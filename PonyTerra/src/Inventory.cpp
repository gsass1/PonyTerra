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
	open = false;
}

CInventory::~CInventory() {
}

void CInventory::Initialize() {
	tilesheet = resMgr->GetTexture("data/res/tex/tilesheet.png");
}

void CInventory::DrawFull() {
	for(int i = 0; i < 9; i++) {
		float spacing = 8.0f;
		float tileWidth = 32.0f;
		float widthPerTile = tileWidth + spacing;
		float paddingX = (graphics->GetSize().x - widthPerTile * 9.0f) / 2.0f;
		float paddingY = widthPerTile * 4.0f + (38.0f * (float)i);
		DrawItemRow(CVector2f(paddingX, paddingY), i);
	}
}

void CInventory::DrawBar() {
	float spacing = 8.0f;
	float tileWidth = 32.0f;
	float widthPerTile = tileWidth + spacing;
	float paddingX = (graphics->GetSize().x - widthPerTile * 9.0f) / 2.0f;
	float paddingY = widthPerTile;
	DrawItemRow(CVector2f(paddingX, paddingY), 0);
}

void CInventory::DrawItemRow(CVector2f pos, int rowIndex) {
	float spacing = 8.0f;
	float tileWidth = 32.0f;
	float widthPerTile = tileWidth + spacing;
	int index = rowIndex * 9;
	for(int j = 0; j < 9; j++) {
		int i = index + j;
		CItem *item = GetItem(i);
		CVector2f tilePos = CVector2f(pos.x + (float)j * widthPerTile, pos.y);
		graphics->DrawTilesheet(tilesheet, tilePos, 16, 16, 16, 64, 64, tileWidth, tileWidth);
		if(item) {
			item->Draw(tilePos);
		}
		if(i == currentSelected) {
			graphics->DrawRect(CRect(tilePos, 32, 32), CColor(255, 255, 255, 128));
		}
	}
}

void CInventory::Draw() {
	if(open) {
		DrawFull();
	} else {
		DrawBar();
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
		if(items[currentSelected]->OnUse()) {
			RemoveItem(currentSelected);
		}
	}
}

void CInventory::Update(float dtTime) {
	if(!open) {
		return;
	}

}

void CInventory::SwitchOpen() {
	open = !open;
}