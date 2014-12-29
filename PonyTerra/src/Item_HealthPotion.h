#ifndef ITEM_HEALTHPOTION_H
#define ITEM_HEALTHPOTION_H

#include "Item.h"

class ITexture;

class CItem_HealthPotion : public CItem {
public:
	CItem_HealthPotion(CEntity *owner);

	void Initialize();
	void OnUse();

	void Draw(CVector2f pos);

private:
	ITexture *tilesheet;
};

#endif