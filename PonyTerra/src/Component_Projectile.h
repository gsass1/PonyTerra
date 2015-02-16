#ifndef COMPONENT_PROJECTILE_H
#define COMPONENT_PROJECTILE_H

#include "Entity.h"
#include "Vector2.h"

class CComponent_Physical;

class CComponent_Projectile : public CComponentBase
{
public:
	CComponent_Projectile(int damage, CEntity *shooter, CVector2f dir);
	~CComponent_Projectile();

	void Initialize(CEntity *parent);
	void Update(float dtTime);

	void HandleMessage(CMessage *msg);

	void Draw();

	int damage;

private:
	CComponent_Physical *phys;
	CEntity *shooter;
	CVector2f dir;
};

#endif