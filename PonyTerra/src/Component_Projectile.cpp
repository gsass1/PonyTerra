#include "Component_Projectile.h"
#include "ICommon.h"
#include "Component_Attributes.h"

CComponent_Projectile::CComponent_Projectile(int damage, CEntity *shooter) : damage(damage), shooter(shooter)
{
}

CComponent_Projectile::~CComponent_Projectile()
{
}

void CComponent_Projectile::Initialize(CEntity *parent)
{
	CComponentBase::Initialize(parent);
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

	auto attributes = GetComponent<CComponent_Attributes>(msgCollideWithEntity->entity);
	if(attributes) {
		/* TODO */
		attributes->UseHealth(damage);
	}

	parent->SignalDeath();
}