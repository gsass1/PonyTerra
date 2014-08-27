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

CGame game_local;

CGame::CGame()
{
	gameState = EGameState::NONE;
	playerEntity = NULL;
    showIngameMenu = false;
}

CGame::~CGame()
{
}

void CGame::Initialize()
{
	gameState = EGameState::MENU;

    console.Initialize();

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
}

void CGame::Quit()
{
}

const char *CGame::GetGameName()
{
	return "PonyTerra";
}

void CGame::OnPrint(const char *msg)
{
    if(console.IsInitialized()) {
        console.Print(msg);
    }
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
    // What to do after the level proc thread
    //
    if(levelProcess.GetStatus() != ELevelProcessType::NONE) {
        ELevelProcessType curProcType = levelProcess.StopThreadIfFinished();
        if(curProcType != ELevelProcessType::NONE) {
            guiManager.ClearStack();
            guiManager.Push(GetGUI("MenuFront"));
            if(curProcType == ELevelProcessType::GENERATE) {
                InitializeGame();
            } else if(curProcType == ELevelProcessType::UNLOAD) {
                gameState = EGameState::MENU;
            } else if(curProcType == ELevelProcessType::SAVE) {
                gameState = EGameState::INGAME;
            } else if(curProcType == ELevelProcessType::SAVE_UNLOAD) {
                gameState = EGameState::MENU;
            } else if(curProcType == ELevelProcessType::LOAD || curProcType == ELevelProcessType::UNLOAD_LOAD) {
                gameState = EGameState::INGAME;
                InitializeGame();
            }
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
        StrUtl::FormatString("Pos: (x: %f y: %f) Cam Pos: (x: %f y: %f)",
        playerPhysical->rect.pos.x,
        playerPhysical->rect.pos.y,
        viewRect.pos.x,
        viewRect.pos.y).c_str());

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

    //viewRect.pos.x = Math::Clamp(viewRect.pos.x, 0.0f, (float)level.width * (float)TILE_SIZE);
    //viewRect.pos.y = Math::Clamp(viewRect.pos.y, 0.0f, (float)level.height * (float)TILE_SIZE);
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
    levelProcess.StartProcess(ELevelProcessType::GENERATE);
}

void CGame::UnloadLevel()
{
    gameState = EGameState::MENU;
    guiManager.Push(GetGUI("Loading"));
    entityMgr.RemoveAll();
    levelProcess.StartProcess(ELevelProcessType::UNLOAD);
}

void CGame::LoadLevel(const std::string &filepath)
{
    gameState = EGameState::MENU;
    guiManager.Push(GetGUI("Loading"));
    levelFilename = filepath;

    if(level.IsLoaded()) {
        levelProcess.StartProcess(ELevelProcessType::UNLOAD_LOAD);
    } else {
        levelProcess.StartProcess(ELevelProcessType::LOAD);
    }
}

void CGame::SaveLevel(const std::string &filepath)
{
    gameState = EGameState::MENU;
    guiManager.Push(GetGUI("Loading"));
    levelFilename = filepath;
    levelProcess.StartProcess(ELevelProcessType::SAVE);
}

void CGame::SaveLevelAndExit(const std::string &filepath)
{
    entityMgr.RemoveAll();
    gameState = EGameState::MENU;
    guiManager.Push(GetGUI("Loading"));
    levelFilename = filepath;
    levelProcess.StartProcess(ELevelProcessType::SAVE_UNLOAD);
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