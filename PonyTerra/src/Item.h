#ifndef ITEM_H
#define ITEM_H

class CEntity;

#include "Vector2.h"

class CItem {
public:
	CItem(CEntity *owner);
	virtual ~CItem() {}

	virtual void Initialize() = 0;
	virtual void OnUse() = 0;

	virtual void Draw(CVector2f pos) = 0;

	static CItem *CreateFromID(CEntity *owner, int id);

protected:
	CEntity *owner;
};

#endif