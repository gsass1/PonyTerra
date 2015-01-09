#ifndef COMPONENT_INVENTORY_H
#define COMPONENT_INVENTORY_H

#include "Entity.h"
#include "Inventory.h"

class CComponent_Inventory : public CComponentBase {
public:
                CComponent_Inventory();

    void        Initialize(CEntity *parent);

    CInventory *inventory;
};

#endif