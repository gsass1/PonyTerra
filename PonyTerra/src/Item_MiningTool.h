#ifndef ITEM_MININGTOOL_H
#define ITEM_MININGTOOL_H

#include "Item.h"
#include "Level.h"

class CItem_MiningTool : public CItem
{
public:
	CItem_MiningTool(CEntity *owner, int strength);
	virtual ~CItem_MiningTool() {}

	void Update(float dtTime);

	bool IsTool() const { return true; }

	void StartMining(CTile *tile);
	void StopMining();

	CTile *GetMinedTile() const { return miningTile; }
	bool IsMining() const { return mining; }
	unsigned int GetMiningTicks() const { return miningTicks; }
	int GetStrength() const { return strength; }

protected:
	CTile *miningTile;
	bool mining;
	unsigned int miningTicks;
	int strength;

	unsigned int miningTime;
};

#endif