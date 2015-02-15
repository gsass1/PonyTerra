#ifndef COMPONENT_PROJECTILE_H
#define COMPONENT_PROJECTILE_H

#include "Entity.h"

class CComponent_Projectile : public CComponentBase
{
public:
	CComponent_Projectile(int damage, CEntity *shooter);
	~CComponent_Projectile();

	void Initialize(CEntity *parent);

	void HandleMessage(CMessage *msg);

	int damage;

private:
	CEntity *shooter;
};

#endif