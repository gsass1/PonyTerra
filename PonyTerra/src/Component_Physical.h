#ifndef COMPONENT_PHYSICAL_H
#define COMPONENT_PHYSICAL_H

#include "Entity.h"
#include "Rect.h"

class CComponent_Physical : public CComponentBase
{
public:
				CComponent_Physical();

	void		Update(float dtTime);

	void		AddVelocity(const CVector2f &v);

	CRect		rect;
	CVector2f	velocity;
	bool		isInAir;
	bool		disableMotion;
};

#endif