#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "Vector2.h"

class CEntity;

class CEntityFactory
{
public:
	CEntityFactory();
	~CEntityFactory();

	CEntity *CreatePlayer();
	CEntity *CreateItemPickup(int itemId);
	CEntity *CreateSpellbookProjectile(CEntity *shooter, CVector2f pos, CVector2f dir);
};

extern CEntityFactory entityFactory;

#endif
