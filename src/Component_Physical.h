#ifndef COMPONENT_PHYSICAL_H
#define COMPONENT_PHYSICAL_H

#include "Entity.h"
#include "Rect.h"

class CComponent_Physical : public CComponentBase
{
public:
	CComponent_Physical();

	void		Update(float dtTime);

	std::string GetID() const;

	void		AddVelocity(const CVector2f &v);

	CRect		rect;
	CVector2f	velocity;
	bool		isInAir;
};

#endif