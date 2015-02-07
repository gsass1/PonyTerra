#include "Item.h"
#include "Item_HealthPotion.h"
#include "Item_Tile.h"

CItem::CItem(CEntity *owner) : owner(owner) {
}


CItem *CItem::CreateFromID(CEntity *owner, int id) {
	CItem *item;
	switch(id) {
	case 256:
		item = new CItem_HealthPotion(owner);
		break;
	default:
		if(id < 256) {
			item = new CItem_Tile(owner, id);
		} else {
			item = nullptr;
		}
		break;
	}
	if(item) {
		item->Initialize();
	}
	return item;
}