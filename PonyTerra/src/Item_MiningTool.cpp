#include "Item_MiningTool.h"
#include "ICommon.h"
#include "Cursor.h"
#include "IInput.h"

CItem_MiningTool::CItem_MiningTool(CEntity *owner, int strength)
	: CItem(owner), strength(strength)
{
	miningTile = nullptr;
	mining = false;
	miningTicks = 0;
	miningTime = 0;
}

void CItem_MiningTool::Update(float dtTime)
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
	unsigned int damageStatus = (currentTicks - miningTicks) / (miningTime / 4) + 1;

	level.SetTileDamageLevel(miningTile, (char)damageStatus);

	if(currentTicks - miningTicks >= miningTime) {
		/* TODO: drop tile pickup */
		level.DestructTile(miningTile);
		StopMining();
	}
}

void CItem_MiningTool::StartMining(CTile *tile)
{
	miningTile = tile;
	mining = true;
	miningTicks = common->GetTicks();
	miningTime = CalculateTileMiningTime(GetTileTypeStrength(tile->type), strength);
}

void CItem_MiningTool::StopMining()
{
	mining = false;
}