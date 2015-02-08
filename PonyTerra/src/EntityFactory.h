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
};

extern CEntityFactory entityFactory;

#endif
