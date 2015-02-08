#include "Component_Animation.h"
#include "Component_Physical.h"
#include "Component_PlayerInput.h"
#include "Component_Inventory.h"
#include "Component_ItemPickup.h"
#include "Component_Attributes.h"
#include "Item.h"
#include "Item_Tile.h"
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

	entity->AddAttribute("player");
	entity->AddAttribute("human");

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
	inventory->inventory->AddItem(256, 1);
	inventory->inventory->AddItem(1, 64);
	inventory->inventory->AddItem(257);

	return entity;
}

CEntity *CEntityFactory::CreateItemPickup(int itemId)
{
	CEntity *entity = new CEntity();

	entity->AddAttribute("pickup");

	CComponent_Physical *phys = new CComponent_Physical();

	phys->rect.width = 32;
	phys->rect.height = 32;

	entity->GetComponents()->Add(phys);
	entity->GetComponents()->Add(new CComponent_ItemPickup(itemId));

	entity->Initialize();

	return entity;
}