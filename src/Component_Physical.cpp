#include "Component_Physical.h"
#include "Level.h"

CComponent_Physical::CComponent_Physical()
{
	velocity.Zero();
}

void CComponent_Physical::Update(float dtTime)
{
	velocity.x *= dtTime;
	velocity.y *= dtTime;

	rect.pos += velocity;

	if(level.IsCollidingWithTiles(rect)) {
		rect.pos -= velocity;
	}

	velocity.Zero();
}

std::string CComponent_Physical::GetID() const
{
	return COMPONENT_PHYSICAL;
}

void CComponent_Physical::AddVelocity(const CVector2f &v)
{
	velocity += v;
}