#ifndef ITEM_PICKAXE_H
#define ITEM_PICKAXE_H

#include "Item.h"

class CTile;
class ITexture;

class CItem_Pickaxe : public CItem
{
public:
	CItem_Pickaxe(CEntity *owner);
	~CItem_Pickaxe();

	void Initialize();
	void Update(float dtTime);

	bool OnUse();

	void Draw(CVector2f pos);

	void StopMining();

	std::string GetName() const;

	bool IsTool() const { return true; }

private:
	ITexture *tilesheet;
	CTile *miningTile;
	bool mining;
	unsigned int miningTicks;
};

#endif