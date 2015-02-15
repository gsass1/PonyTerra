#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

class CEntity;

class CEntityFactory
{
public:
	CEntityFactory();
	~CEntityFactory();

	CEntity *CreatePlayer();
	CEntity *CreateItemPickup(int itemId);
	CEntity *CreateSpellbookProjectile(CEntity *shooter);
};

extern CEntityFactory entityFactory;

#endif
