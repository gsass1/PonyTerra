#include "Item.h"
#include "Item_HealthPotion.h"

CItem::CItem(CEntity *owner) : owner(owner) {
}


CItem *CItem::CreateFromID(CEntity *owner, int id) {
    CItem *item;
    switch(id) {
    case 0:
        item = new CItem_HealthPotion(owner);
        break;
    default:
        item = nullptr;
        break;
    }
    if(item) {
        item->Initialize();
    }
    return item;
}