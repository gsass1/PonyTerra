#include "ICommon.h"
#include "Inventory.h"
#include "IResourceManager.h"
#include "IGraphics.h"
#include "Item.h"

CInventory::CInventory(CEntity *owner, int size) : owner(owner), size(size) {
	items = new CItem*[size];
	for(int i = 0; i < size; i++) {
		items[i] = nullptr;
	}
	currentSelected = 0;
}

CInventory::~CInventory() {
}

void CInventory::Initialize() {
	tilesheet = resMgr->GetTexture("data/res/tex/tilesheet.png");
}

void CInventory::DrawFull() {
}

void CInventory::DrawBar() {
	float spacing = 8.0f;
	float tileWidth = 32.0f;
	float widthPerTile = tileWidth + spacing;
	float paddingX = (graphics->GetSize().x - widthPerTile * 9.0f) / 2.0f;
	float paddingY = widthPerTile;
	for(int i = 0; i < 9; i++) {
		CItem *item = GetItem(i);
		CVector2f pos = CVector2f(paddingX + (float)i * widthPerTile, paddingY);
		graphics->DrawTilesheet(tilesheet, pos, 16, 16, 16, 64, 64, tileWidth, tileWidth);
		if(item) {
			item->Draw(pos);
		}
		if(i == currentSelected) {
			graphics->DrawRect(CRect(pos, 32, 32), CColor(255, 255, 255, 128));
		}
	}
}

bool CInventory::AddItem(CItem *item) {
	for(int i = 0; i < size; i++) {
		if(items[i] == nullptr) {
			items[i] = item;
			return true;
		}
	}
	return false;
}

CItem *CInventory::GetItem(int index) {
	ASSERT(index >= 0);
	ASSERT(index < size);

	return items[index];
}

const CItem *CInventory::GetItem(int index) const {
	ASSERT(index >= 0);
	ASSERT(index < size);

	return items[index];
}

void CInventory::RemoveItem(int index) {
	auto item = GetItem(index);
	if(item) {
		delete item;
		items[index] = nullptr;
	}
}

void CInventory::UseCurrentItem() {
	if(items[currentSelected]) {
		items[currentSelected]->OnUse();
		RemoveItem(currentSelected);
	}
}