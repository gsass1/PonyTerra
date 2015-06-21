#include "Item_Pickaxe.h"
#include "IResourceManager.h"
#include "IGraphics.h"
#include "Cursor.h"
#include "Level.h"
#include "ICommon.h"
#include "IInput.h"
#include "Game.h"
#include <SDL/SDL_opengl.h>

CItem_Pickaxe::CItem_Pickaxe(CEntity *owner) : CItem_MiningTool(owner, 300)
{
	tilesheet = nullptr;
}

CItem_Pickaxe::~CItem_Pickaxe()
{
}

void CItem_Pickaxe::Initialize()
{
	tilesheet = resMgr->GetTexture("data/res/tex/tilesheet.png");
}

void CItem_Pickaxe::Update(float dtTime)
{
	CItem_MiningTool::Update(dtTime);
}

bool CItem_Pickaxe::OnUse()
{
	if(IsMining()) {
		return false;
	}

	if(!cursor.currentSelectedTile) {
		return false;
	}

	if(cursor.currentSelectedTile->type == ETileType::AIR) {
		return false;
	}

	StartMining(cursor.currentSelectedTile);
	return false;
}

void CItem_Pickaxe::Draw(CVector2f pos)
{
	graphics->DrawTilesheet(tilesheet, pos, 48, 16, 16, 64, 64, 32.0f, 32.0f);
}
