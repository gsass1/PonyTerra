#ifndef INVENTORY_H
#define INVENTORY_H

#include "Vector2.h"

class CEntity;
class CItem;
class IFont;
class ITexture;

struct SItemStack
{
	SItemStack()
	{
		count = 0;
		item = nullptr;
	}

	int count;
	CItem *item;
};

class CInventory {
public:
	CInventory(CEntity *owner, int size = 81);
	~CInventory();

	void Initialize();
	void DrawFull();
	void DrawBar();
	void DrawItemRow(CVector2f pos, int rowIndex);
	void Draw();

	bool AddItem(CItem *item, int count = 1);

	CItem *GetItem(int index);
	const CItem *GetItem(int index) const;

	SItemStack *GetItemStack(int index);

	void DecrementStack(int index);
	void RemoveItem(int index);

	void UseCurrentItem();

	void Update(float dtTime);

	void SwitchOpen();

	SItemStack *GetCurrentSelectedItemStack();

	int currentSelected;

private:
	bool open;
	int size;
	SItemStack **items;
	CEntity *owner;
	ITexture *tilesheet;
	IFont *font;

	void DrawItemStackTile(const CVector2f &pos, SItemStack *itemStack);
};

#endif