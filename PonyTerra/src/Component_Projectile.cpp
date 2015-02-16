#include "Component_Projectile.h"
#include "ICommon.h"
#include "Component_Attributes.h"
#include "Component_Physical.h"
#include "IGraphics.h"
#include "Game.h"

CComponent_Projectile::CComponent_Projectile(int damage, CEntity *shooter, CVector2f dir)
	: damage(damage), shooter(shooter), dir(dir)
{
	phys = nullptr;
}

CComponent_Projectile::~CComponent_Projectile()
{
}

void CComponent_Projectile::Initialize(CEntity *parent)
{
	CComponentBase::Initialize(parent);
	phys = GetComponent<CComponent_Physical>(parent);
}

void CComponent_Projectile::Update(float dtTime)
{
	/* TODO: put speed somewhere else? */
	phys->AddVelocity(CVector2f(100.0f) * dir);

	if(phys->velocity.x > 300.0f) {
		phys->velocity.x = 300.0f;
	}
}

void CComponent_Projectile::HandleMessage(CMessage *msg)
{
	if(msg->GetType() == EMessageType::COLLIDE) {
		/* Collided with ground, die */
		parent->SignalDeath();
		return;
	}

	if(msg->GetType() != EMessageType::COLLIDE_WITH_ENTITY) {
		return;
	}

	auto msgCollideWithEntity = (CMessage_CollideWithEntity *)msg;
	ASSERT(msgCollideWithEntity);

	if(msgCollideWithEntity->entity == shooter) {
		return;
	}

	if(!msgCollideWithEntity->entity->HasAttribute("creature")) {
		return;
	}

	auto attributes = GetComponent<CComponent_Attributes>(msgCollideWithEntity->entity);
	if(attributes) {
		/* TODO */
		attributes->UseHealth(damage);
	}

	parent->SignalDeath();
}

void CComponent_Projectile::Draw()
{
	graphics->DrawRect(CRect(game_local.ToScreenSpace(phys->rect.pos), 16, 8), CColor(0, 0, 255));
}