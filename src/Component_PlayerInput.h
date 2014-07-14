#ifndef COMPONENT_PLAYERINPUT_H
#define COMPONENT_PLAYERINPUT_H

#include "Entity.h"

class CComponent_Physical;

class CComponent_PlayerInput : public CComponentBase
{
public:
	CComponent_PlayerInput();

	void Initialize(CEntity *parent);

	void Update(float dtTime);

private:
	CComponent_Physical *physical;
};

#endif