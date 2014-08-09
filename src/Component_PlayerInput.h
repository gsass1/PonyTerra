#ifndef COMPONENT_PLAYERINPUT_H
#define COMPONENT_PLAYERINPUT_H

#include "Entity.h"

class CComponent_Animation;
class CComponent_Physical;

class CComponent_PlayerInput : public CComponentBase
{
public:
	CComponent_PlayerInput();

	void Initialize(CEntity *parent);

	void Update(float dtTime);

	void SetNoClip(bool noclip);
	bool ToggleNoClip();

private:
	CComponent_Animation *animation;
	CComponent_Physical *physical;
	bool noclip;

	void UpdateNoClip(float dtTime);
};

#endif