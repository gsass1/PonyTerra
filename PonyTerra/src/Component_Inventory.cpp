#include "Component_Inventory.h"

CComponent_Inventory::CComponent_Inventory() {
	inventory = nullptr;
}

void CComponent_Inventory::Initialize(CEntity *parent) {
	CComponentBase::Initialize(parent);

	inventory = new CInventory(parent, 9 * 9);
	inventory->Initialize();
}