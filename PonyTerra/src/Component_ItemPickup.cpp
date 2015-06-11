#include "Component_ItemPickup.h"
#include "EntityManager.h"
#include "Component_Inventory.h"
#include "Item.h"
#include "IResourceManager.h"
#include "IGraphics.h"
#include "Component_Physical.h"
#include "ICommon.h"
#include "MathUtil.h"

const int PICKUP_DELAY_AFTER_BIRTH = 5000;

CComponent_ItemPickup::CComponent_ItemPickup(int id) : CComponentBase()
{
	itemId = id;
	birthTicks = 0;
	pickingUpEntity = nullptr;
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
	if(pickingUpEntity) {
		float angle = phys->rect.pos.AngleTo(GetComponent<CComponent_Physical>(pickingUpEntity)->rect.pos);
		CVector2f dir(Math::Sinf(angle), Math::Cosf(angle));
		phys->AddVelocity(dir * 10.0f);
	}
}

void CComponent_ItemPickup::HandleMessage(CMessage *msg)
{
	if(msg->GetType() == EMessageType::COLLIDE_WITH_ENTITY) {
		auto msgCollideWithEntity = (const CMessage_CollideWithEntity *)(msg);
		ASSERT(msgCollideWithEntity);

		if(msgCollideWithEntity->entity->HasAttribute("player")) {
			pickingUpEntity = msgCollideWithEntity->entity;
			CVector2f dist = phys->rect.pos - GetComponent<CComponent_Physical>(msgCollideWithEntity->entity)->rect.pos;
			float distance = Math::Sqrtf(std::powf(dist.x, 2.0f) + std::powf(dist.y, 2.0f));

			if(distance > 100.0f) {
				pickingUpEntity = nullptr;
				return;
			}

			if(distance < 64.0f) {
				auto inv = GetComponent<CComponent_Inventory>(msgCollideWithEntity->entity);
				if(inv) {
					inv->inventory->AddItem(itemId);
				}
				/* Destroy self */
				parent->SignalDeath();
			}
		}
	}
}

void CComponent_ItemPickup::Draw()
{
	float bobbing = std::fabs(Math::Sinf((float)(common->GetTicks() - birthTicks) / 1000.0f) * 10.0f);
	CVector2f pos = phys->rect.pos;
	pos.y += bobbing;

	graphics->DrawTilesheet(tilesheet, game_local.ToScreenSpace(pos), itemId, 16, 16, 64, 64, 32.0f, 32.0f);
}