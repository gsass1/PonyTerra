#include "Component_Animation.h"
#include "Component_Physical.h"
#include "Component_PlayerInput.h"
#include "Component_Inventory.h"
#include "Component_Attributes.h"
#include "Item.h"

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
	entity->GetComponents()->Add(new CComponent_Inventory());
	entity->GetComponents()->Add(new CComponent_Attributes());

	CComponent_Animation *animation = new CComponent_Animation();

	animation->Load("twilight_sparkle");

	entity->GetComponents()->Add(animation);

	entity->Initialize();


	auto inventory = GetComponent<CComponent_Inventory>(entity);
	inventory->inventory->AddItem(CItem::CreateFromID(entity, 0));

	return entity;
}