#ifndef COMPONENT_ITEMPICKUP_H
#define COMPONENT_ITEMPICKUP_H

#include "Entity.h"
#include "Game.h"

class CComponent_Physical;

class ITexture;

class CComponent_ItemPickup : public CComponentBase
{
public:
	CComponent_ItemPickup(int id);

	void Initialize(CEntity *parent);

	void Update(float dtTime);
	void Draw();

private:
	int itemId;
	ITexture *tilesheet;
	CComponent_Physical *phys;
	unsigned int birthTicks;
};

#endif