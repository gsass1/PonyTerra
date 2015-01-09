#ifndef INVENTORY_H
#define INVENTORY_H

#include "Vector2.h"

class CEntity;
class CItem;
class ITexture;

class CInventory {
public:
					CInventory(CEntity *owner, int size = 81);
					~CInventory();

	void			Initialize();
	void			DrawFull();
	void			DrawBar();
	void			DrawItemRow(CVector2f pos, int rowIndex);
	void			Draw();

	bool			AddItem(CItem *item);

	CItem *			GetItem(int index);
	const CItem *	GetItem(int index) const;

	void			RemoveItem(int index);

	void			UseCurrentItem();

	void			Update(float dtTime);

	void			SwitchOpen();

	int				currentSelected;

private:
	bool			open;
	int				size;
	CItem **		items;
	CEntity *		owner;
	ITexture *		tilesheet;
};

#endif