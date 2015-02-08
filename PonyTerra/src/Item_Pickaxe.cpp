#include "Item_Pickaxe.h"
#include "IResourceManager.h"
#include "IGraphics.h"
#include "Cursor.h"
#include "Level.h"
#include "ICommon.h"
#include "IInput.h"

/* TODO: compute this with the pickaxe strength and mined block type */
#define MINING_TIME_TICKS 1000

CItem_Pickaxe::CItem_Pickaxe(CEntity *owner) : CItem(owner)
{
	mining = false;
	miningTicks = 0;
	miningTile = nullptr;
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
	if(!mining) {
		return;
	}

	/* Cursor has left the mining tile */
	if(cursor.currentSelectedTile != miningTile) {
		StopMining();
		return;
	}

	/* Left mouse button has to be pressed */
	/* FIXME: this should not be dependent of raw input functions */
	if(!(input->GetMouseState().buttonMask & EMouseButton_LEFT)) {
		StopMining();
		return;
	}

	unsigned int currentTicks = common->GetTicks();
	if(currentTicks - miningTicks >= MINING_TIME_TICKS) {
		/* TODO: drop tile pickup */
		level.RemoveTile(miningTile);
		StopMining();
	}
}

void CItem_Pickaxe::StopMining()
{
	mining = false;
	miningTile = nullptr;
}

bool CItem_Pickaxe::OnUse()
{
	if(!cursor.currentSelectedTile) {
		return false;
	}

	if(cursor.currentSelectedTile->type == ETileType::AIR) {
		return false;
	}

	/* Start mining! */
	mining = true;
	miningTile = cursor.currentSelectedTile;
	miningTicks = common->GetTicks();
	return false;
}

void CItem_Pickaxe::Draw(CVector2f pos)
{
	graphics->DrawTilesheet(tilesheet, pos, 48, 16, 16, 64, 64, 32.0f, 32.0f);
}

std::string CItem_Pickaxe::GetName() const
{
	return "Pickaxe";
}