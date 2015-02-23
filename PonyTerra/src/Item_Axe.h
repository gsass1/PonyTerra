#ifndef ITEM_AXE_H
#define ITEM_AXE_H

#include "Item_MiningTool.h"

class CTile;
class ITexture;

class CItem_Axe : public CItem_MiningTool
{
public:
	CItem_Axe(CEntity *owner);
	~CItem_Axe();

	void Initialize();
	void Update(float dtTime);

	bool OnUse();

	void Draw(CVector2f pos);

	std::string GetName() const { return "Axe"; }

private:
	ITexture *tilesheet;
};

#endif