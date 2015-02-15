#include "Component_ItemPickup.h"
#include "EntityManager.h"
#include "Component_Inventory.h"
#include "Item.h"
#include "IResourceManager.h"
#include "IGraphics.h"
#include "Component_Physical.h"
#include "ICommon.h"
#include "MathUtil.h"

CComponent_ItemPickup::CComponent_ItemPickup(int id) : CComponentBase()
{
	itemId = id;
	birthTicks = 0;
}

void CComponent_ItemPickup::Initialize(CEntity *parent)
{
	CComponentBase::Initialize(parent);
	tilesheet = resMgr->GetTexture("data/res/tex/tilesheet.png");

	phys = parent->GetComponents()->Get<CComponent_Physical>();
	birthTicks = common->GetTicks();
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
	float bobbing = std::fabs(Math::Sinf((float)(common->GetTicks() - birthTicks) / 1000.0f) * 10.0f);
	CVector2f pos = phys->rect.pos;
	pos.y += bobbing;

	graphics->DrawTilesheet(tilesheet, game_local.ToScreenSpace(pos), itemId, 16, 16, 64, 64, 32.0f, 32.0f);
}