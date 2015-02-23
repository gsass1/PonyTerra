#include "Item_Axe.h"
#include "Level.h"
#include "IGraphics.h"
#include "IResourceManager.h"
#include "IInput.h"
#include "Cursor.h"
#include "ICommon.h"

#define MINING_TIME_TICKS 2500

CItem_Axe::CItem_Axe(CEntity *owner) : CItem_MiningTool(owner, 250)
{
	tilesheet = nullptr;
}

CItem_Axe::~CItem_Axe()
{
}

void CItem_Axe::Initialize()
{
	tilesheet = resMgr->GetTexture("data/res/tex/tilesheet.png");
}

void CItem_Axe::Update(float dtTime)
{
	CItem_MiningTool::Update(dtTime);
}

bool CItem_Axe::OnUse()
{
	if(IsMining()) {
		return false;
	}

	if(!cursor.currentSelectedTile) {
		return false;
	}

	if(cursor.currentSelectedTile->type != ETileType::WOOD) {
		return false;
	}

	StartMining(cursor.currentSelectedTile);
	return false;
}

void CItem_Axe::Draw(CVector2f pos)
{
	graphics->DrawTilesheet(tilesheet, pos, 48, 16, 16, 64, 64, 32.0f, 32.0f);
}