#include "Component_GameEntity.h"

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

	// add player components

	entity->GetComponents()->Add(new CComponent_GameEntity());

	entity->Initialize();

	return entity;
}