#include "Component_Physical.h"
#include "ICommon.h"
#include "IFont.h"
#include "EntityFactory.h"
#include "EntityManager.h"
#include "Game.h"
#include "IGraphics.h"
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
	bool generating = false;

	{
		CMutexLock lock(&levelGenerate.stateLock);
		generating = levelGenerate.isGenerating;
	}

	if (!generating && level.IsLoaded()) {
		try {
			if (levelGenThread->joinable()) {
                levelGenThread->join();
                //delete levelGenThread;
				levelGenerate.isGenerating = false;
				InitializeGame();
			}
		}
        catch(std::exception &e) {
            common->Error("%s\n", e.what());
		}
	}

	switch(gameState) {
		case EGameState::MENU:
			guiManager.Update(dtTime);
			break;

		case EGameState::INGAME:
			entityMgr.UpdateAll(dtTime);
			LookAt(playerEntity->GetComponents()->Get<CComponent_Physical>()->rect);
			break;
	}
}

void CGame::Draw()
{
	switch(gameState) {
		case EGameState::MENU:
			guiManager.Draw();
			break;

		case EGameState::INGAME:
			level.Draw();

			CComponent_Physical *playerPhysical = playerEntity->GetComponents()->Get<CComponent_Physical>();

			CRect drawRect = playerPhysical->rect;
			drawRect.pos -= viewRect.pos;

			graphics->DrawRect(drawRect, CColor(255, 0, 0));

			graphics->DrawText(
				resMgr->GetFont("data/res/font/sys.fnt"), 
				CVector2f(0.0f, (float)graphics->GetHeight() - 20.0f), 
				CColor::white, 
				StrUtl::FormatString("Player pos: %f:%f",
				playerPhysical->rect.pos.x,
				playerPhysical->rect.pos.y).c_str());

			break;
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