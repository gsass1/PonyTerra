#include "Precompiled.h"


#include "Component_Physical.h"
#include "Level.h"

#define MAX_GRAVITY 1000.0f

CComponent_Physical::CComponent_Physical()
{
	velocity.Zero();
	isInAir = false;
	disableMotion = false;
}

void CComponent_Physical::Update(float dtTime)
{
	if(disableMotion) {
		return;
	}

	float xVel = velocity.x * dtTime;
	rect.pos.x += xVel;
	if(level.IsCollidingWithTiles(rect)) {
		rect.pos.x -= xVel;
		velocity.x = 0.0f;
	} else {
		velocity.x *= 0.9f;
	}

	float yVel = velocity.y * dtTime;
	rect.pos.y += yVel;
	if(level.IsCollidingWithTiles(rect)) {
		rect.pos.y -= yVel;
		if(velocity.y > 0.0f) {
			velocity.y = -64.0f;
		} else {
			velocity.y = 0.0f;
			isInAir = false;
			while(level.IsCollidingWithTiles(rect)) {
				rect.pos.y += 1.0f;
			}
		}
	} else {
		if(velocity.y < 0.0f) {
			if(velocity.y < -MAX_GRAVITY) {
				velocity.y = -MAX_GRAVITY;
			} else {
				velocity.y *= 1.08f;
			}
		} else {
			velocity.y *= 0.85f;
		}
		if(!isInAir || (isInAir && velocity.y > -10.0f)) {
			isInAir = true;
			velocity.y -= 64.0f;
		}
	}
}

void CComponent_Physical::AddVelocity(const CVector2f &v)
{
	velocity += v;
}