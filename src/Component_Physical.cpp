#include "Component_Physical.h"

void CComponent_Physical::Update(float dtTime)
{
	rect.pos += velocity;
}

std::string CComponent_Physical::GetID() const
{
	return COMPONENT_PHYSICAL;
}