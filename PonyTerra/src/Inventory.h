#ifndef INVENTORY_H
#define INVENTORY_H

class CEntity;
class CItem;
class ITexture;

class CInventory {
public:
	CInventory(CEntity *owner, int size);
	~CInventory();

	void Initialize();
	void DrawFull();
	void DrawBar();

	bool AddItem(CItem *item);

	CItem *GetItem(int index);
	const CItem *GetItem(int index) const;

	void RemoveItem(int index);

	void UseCurrentItem();

	int currentSelected;

private:
	int size;
	CItem **items;
	CEntity *owner;
	ITexture *tilesheet;
};

#endif