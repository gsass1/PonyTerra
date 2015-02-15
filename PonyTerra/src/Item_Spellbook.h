#ifndef ITEM_SPELLBOOK_H
#define ITEM_SPELLBOOK_H

#include "Item.h"

class CComponent_Attributes;
class ITexture;

class CItem_Spellbook : public CItem
{
public:
	CItem_Spellbook(CEntity *owner);
	~CItem_Spellbook();

	void Initialize();
	void Update(float dtTime);

	bool OnUse();

	void Draw(CVector2f pos);

	std::string GetName() const { return "Spellbook"; }
	bool IsTool() const { return false; }

private:
	CComponent_Attributes *attributes;
	ITexture *tilesheet;
};

#endif