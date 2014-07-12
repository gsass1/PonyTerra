#include "Component_Physical.h"
#include "Component_PlayerInput.h"

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

	physical->rect.width = 120;
	physical->rect.height = 60;

	entity->GetComponents()->Add(physical);

	entity->GetComponents()->Add(new CComponent_PlayerInput());

	entity->Initialize();

	return entity;
}