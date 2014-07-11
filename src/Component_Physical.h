#ifndef COMPONENT_PHYSICAL_H
#define COMPONENT_PHYSICAL_H

#include "Entity.h"
#include "Rect.h"

class CComponent_Physical : public CComponentBase
{
public:
	void		Update(float dtTime);

	std::string GetID() const;

	CRect		rect;
	CVector2f	velocity;
};

#endif