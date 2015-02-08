#ifndef ITEM_H
#define ITEM_H

class CEntity;

#include "Vector2.h"
#include <string>

class CItem {
public:
	CItem(CEntity *owner);
	virtual ~CItem() {}

	virtual void Initialize() = 0;
	virtual bool OnUse() = 0;

	virtual void Update(float dtTime) = 0;
	virtual void Draw(CVector2f pos) = 0;

	virtual std::string GetName() const = 0;

	static CItem *CreateFromID(CEntity *owner, int id);

	int GetID() const
	{
		return id;
	}

protected:
	CEntity *owner;
	int id;
};

#endif