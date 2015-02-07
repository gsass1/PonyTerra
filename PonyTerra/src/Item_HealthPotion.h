#ifndef ITEM_HEALTHPOTION_H
#define ITEM_HEALTHPOTION_H

#include "Item.h"

class ITexture;

class CItem_HealthPotion : public CItem {
public:
	CItem_HealthPotion(CEntity *owner);

	void Initialize();
	bool OnUse();

	void Update(float dtTime);
	void Draw(CVector2f pos);

private:
	ITexture *tilesheet;

	unsigned int lastTicks;
	int animState;
};

#endif