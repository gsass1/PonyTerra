#include "Component_ItemPickup.h"
#include "EntityManager.h"
#include "Component_Inventory.h"
#include "Item.h"
#include "IResourceManager.h"
#include "IGraphics.h"
#include "Component_Physical.h"

CComponent_ItemPickup::CComponent_ItemPickup(int id) : CComponentBase()
{
	itemId = id;
}

void CComponent_ItemPickup::Initialize(CEntity *parent)
{
	CComponentBase::Initialize(parent);
	tilesheet = resMgr->GetTexture("data/res/tex/tilesheet.png");

	phys = parent->GetComponents()->Get<CComponent_Physical>();
}

void CComponent_ItemPickup::Update(float dtTime)
{
	CEntity *nearbyEntity = entityMgr.GetNearbyEntity(parent, 64.0f);
	if(!nearbyEntity) {
		return;
	}

	/* Only players can pickup stuff? */
	if(!(nearbyEntity->HasAttribute("player"))) {
		return;
	}

	auto phys = GetComponent<CComponent_Physical>(nearbyEntity);
	if(!phys) {
		return;
	}

	if(!phys->rect.Collides(this->phys->rect)) {
		return;
	}

	auto inv = GetComponent<CComponent_Inventory>(nearbyEntity);
	if(inv) {
		inv->inventory->AddItem(itemId);
	}

	/* Destroy self */
	parent->SignalDeath();
}

void CComponent_ItemPickup::Draw()
{
	graphics->DrawTilesheet(tilesheet, game_local.ToScreenSpace(phys->rect.pos), itemId, 16, 16, 64, 64, 32.0f, 32.0f);
}