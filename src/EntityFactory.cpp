#include "Component_Physical.h"

#include "Entity.h"
#include "EntityFactory.h"

CEntityFactory entityFactory;

CEntityFactory::CEntityFactory()
{
}

CEntityFactory::~CEntityFactory()
{
}

CEntity *CEntityFactory::CreatePlayer()
{
	CEntity *entity = new CEntity();

	CComponent_Physical *physical = new CComponent_Physical();

	physical->rect.width = 190;
	physical->rect.width = 60;

	entity->GetComponents()->Add(physical);

	entity->Initialize();

	return entity;
}