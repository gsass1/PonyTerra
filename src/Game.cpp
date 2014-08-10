#include "Component_Physical.h"
#include "Component_PlayerInput.h"
#include "Console.h"
#include "ICommon.h"
#include "IFont.h"
#include "EntityFactory.h"
#include "EntityManager.h"
#include "Game.h"
#include "IGraphics.h"
#include "IInput.h"
#include "GUIManager.h"
#include "Level.h"
#include "IResourceManager.h"
#include "ITexture.h"

#include "MutexLock.h"
#include "VersionNumber.h"

#include "StringUtils.h"

static bool IsLevelGenerating()
{
    CMutexLock lock(&levelGenerate.stateLock);
    return levelGenerate.isGenerating;
}

CGame game_local;

CGame::CGame()
{
	gameState = EGameState::NONE;
	playerEntity = NULL;
    showIngameMenu = false;
}

CGame::~CGame()
{
	delete playerEntity;
}

void CGame::Initialize()
{
	gameState = EGameState::MENU;

	common->Printf("PonyTerra %d.%d.%d.%d\n", PONYTERRA_MAJOR, PONYTERRA_MINOR, PONYTERRA_REV, PONYTERRA_BUILD);

	PreloadMenuData();

	level.Initialize();

	guiManager.Initialize();
	guiManager.Push(GetGUI("MenuFront"));
}

void CGame::InitializeGame()
{
	gameState = EGameState::INGAME;
	playerEntity = entityFactory.CreatePlayer();
	entityMgr.AddEntity(playerEntity);
	playerEntity->GetComponents()->Get<CComponent_Physical>()->rect.pos.Set(0.0f, 500.0f);
}

void CGame::Quit()
{
}

const char *CGame::GetGameName()
{
	return "PonyTerra";
}

void CGame::PreloadMenuData()
{
	resMgr->GetTexture("data/res/tex/menu_bg.png");
	resMgr->GetFont("data/res/font/menu.fnt");
}

void CGame::ReleaseMenuData()
{
	resMgr->ClearCache("data/res/tex/menu_bg.png");
	resMgr->ClearCache("data/res/font/menu.fnt");
}

void CGame::Update(float dtTime)
{
    //
    // Stop the level gen thread
    //
	if (!IsLevelGenerating() && level.IsLoaded()) {
			if (levelGenThread->joinable()) {
                levelGenThread->join();

				levelGenerate.isGenerating = false;

                guiManager.ClearStack();
                guiManager.Push(GetGUI("MenuFront"));

				InitializeGame();
			}
	}

    if(input->KeyPressed(NSKey::NSK_F1, true)) {
        console.ToggleFocus();
    }

    console.Update(dtTime);

	switch(gameState) {
		case EGameState::MENU:
            UpdateMenu(dtTime);
			break;

		case EGameState::INGAME:
            UpdateGame(dtTime);
			break;
	}
}

void CGame::UpdateMenu(float dtTime)
{
    guiManager.Update(dtTime);
}

void CGame::UpdateGame(float dtTime)
{
    if(input->KeyPressed(NSKey::NSK_ESCAPE, true)) {
        ToggleShowIngameMenu();
    }

    if(showIngameMenu) {
        guiManager.Update(dtTime);

        //
        // Ingame menu may have unloaded the level
        // so check this and return immediately
        //
        if(gameState == EGameState::MENU) {
            return;
        }

    }

    entityMgr.UpdateAll(dtTime);
    LookAt(GetComponent<CComponent_Physical>(playerEntity)->rect);

    if(input->KeyPressed(NSKey::NSK_F2, true)) {
        GetComponent<CComponent_PlayerInput>(playerEntity)->ToggleNoClip();
    }
}

void CGame::Draw()
{
	switch(gameState) {
		case EGameState::MENU:
            DrawMenu();
			break;

		case EGameState::INGAME:
            DrawGame();
			break;
	}

    console.Draw();
}

void CGame::DrawMenu()
{
    guiManager.Draw();
}

void CGame::DrawGame()
{
    level.Draw();

    entityMgr.DrawAll();

    CComponent_Physical *playerPhysical = playerEntity->GetComponents()->Get<CComponent_Physical>();

    graphics->DrawText(
        resMgr->GetFont("data/res/font/sys.fnt"),
        CVector2f(0.0f, (float)graphics->GetHeight() - 20.0f),
        CColor::white,
        StrUtl::FormatString("Pos: (x: %f y:%f)",
        playerPhysical->rect.pos.x,
        playerPhysical->rect.pos.y).c_str());

    if(showIngameMenu) {
        guiManager.Draw();
    }
}

void CGame::LookAt(const CRect &rect)
{
	viewRect.width = graphics->GetWidth();
	viewRect.height = graphics->GetHeight();

	viewRect.pos.x = rect.pos.x + (float)rect.width / 2.0f - (float)viewRect.width / 2.0f;
	viewRect.pos.y = rect.pos.y + (float)rect.height / 2.0f - (float)viewRect.height / 2.0f;
}

CRect CGame::GetViewRect() const
{
	return viewRect;
}

CEntity *CGame::GetPlayerEntity() const
{
	return playerEntity;
}

void CGame::BeginLevelGenProccess(int levelWidth, int levelHeight)
{
    if(gameState == EGameState::INGAME) {
        UnloadLevel();
    }

    if(showIngameMenu) {
        ToggleShowIngameMenu();
    }

    gameState = EGameState::MENU;
    guiManager.Push(GetGUI("Loading"));
    level.width = levelWidth;
    level.height = levelHeight;
    levelGenerate.StartGenerating();
}

void CGame::UnloadLevel()
{
    entityMgr.RemoveAll();
    level.Clear();
    gameState = EGameState::MENU;
    guiManager.ClearStack();
    guiManager.Push(GetGUI("MenuFront"));
}

void CGame::ToggleShowIngameMenu()
{
    showIngameMenu = !showIngameMenu;
    if(showIngameMenu) {
        guiManager.ClearStack();
        guiManager.Push(GetGUI("IngameMenu"));
    } else {
        guiManager.ClearStack();
    }
}

bool CGame::KeyPressedIngame(NSKey key, bool once)
{
    if(gameState == EGameState::INGAME && !console.HasFocus() && !showIngameMenu) {

        return input->KeyPressed(key, once);
    } else {
        return false;
    }
}