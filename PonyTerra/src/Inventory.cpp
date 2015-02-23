#include "ICommon.h"
#include "Inventory.h"
#include "IResourceManager.h"
#include "IGraphics.h"
#include "Item.h"
#include "StringUtils.h"
#include "IInput.h"

CInventory::CInventory(CEntity *owner, int size) : owner(owner), size(size) {
	items = new SItemStack*[size];
	for(int i = 0; i < size; i++) {
		items[i] = nullptr;
	}
	currentSelected = 0;
	open = false;
}

CInventory::~CInventory() {
	delete [] items;
}

void CInventory::Initialize() {
	font = resMgr->GetFont("data/res/font/bar.fnt");
	tilesheet = resMgr->GetTexture("data/res/tex/tilesheet.png");
}

void CInventory::Update(float dtTime)
{
	for(int i = 0; i < 9 * 9; i++) {
		auto item = GetItem(i);
		if(item) {
			item->Update(dtTime);
		}
	}

	/* input->GetMouseState is ugly */
	int selected;
	CVector2f mousePos = CVector2f(input->GetMouseState().x, input->GetMouseState().y);
	CRect mouseRect(mousePos, 1, 1);

	float spacing = 8.0f;
	float tileWidth = 32.0f;
	float widthPerTile = tileWidth + spacing;
	float paddingX = (graphics->GetSize().x - widthPerTile * 9.0f) / 2.0f;
	for(int i = 0; i < 9; i++) {
		float paddingY = widthPerTile * 4.0f + (38.0f * (float)i);
		for(int j = 0; j < 9; j++) {
			int fullIndex = i * 9 + j;
			CRect itemFrameRect(CVector2f(paddingX + i * 40.0f, paddingY + j * 40.0f), 32, 32);
			if(mouseRect.Collides(itemFrameRect)) {
				/* TODO: */
			}
		}
	}
}

void CInventory::DrawFull() {
	float spacing = 8.0f;
	float tileWidth = 32.0f;
	float widthPerTile = tileWidth + spacing;
	float paddingX = (graphics->GetSize().x - widthPerTile * 9.0f) / 2.0f;
	float paddingY = 140.0f;

	graphics->DrawText(font, CVector2f(graphics->GetSize().x / 2.0f, paddingY + widthPerTile * 9.0f + 8.0f), CColor(0, 0, 0), "Inventory", true);
	graphics->DrawRect(CRect(CVector2f(paddingX - 8.0f, paddingY - 8.0f), (int)widthPerTile * 9 + 8.0f, (int)widthPerTile * 9 + 8.0f), CColor::white);

	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			int index = i * 9 + j;
			SItemStack *itemStack = GetItemStack(index);
			CVector2f tilePos = CVector2f(paddingX + (float)j * widthPerTile, paddingY + (float)i * widthPerTile);
			graphics->DrawTilesheet(tilesheet, tilePos, 16, 16, 16, 64, 64, tileWidth, tileWidth);
			if(itemStack && itemStack->item) {
				DrawItemStackTile(tilePos, itemStack);
			}
		}
	}
}

void CInventory::DrawBar() {
	float spacing = 8.0f;
	float tileWidth = 32.0f;
	float widthPerTile = tileWidth + spacing;
	float paddingX = (graphics->GetSize().x - widthPerTile * 9.0f) / 2.0f;
	float paddingY = widthPerTile;
	
	graphics->DrawRect(CRect(CVector2f(paddingX - 8.0f, paddingY - 8.0f), (int)widthPerTile * 9 + 8.0f, (int)widthPerTile + 8.0f), CColor::white);
	DrawItemRow(CVector2f(paddingX, paddingY), 0);

	auto currentItem = GetItemStack(currentSelected);
	if(currentItem && currentItem->item) {
		graphics->DrawText(font, CVector2f(graphics->GetSize().x / 2.0f, paddingY + 80.0f), CColor::white, currentItem->item->GetName(), true);
	}
}

void CInventory::DrawItemRow(CVector2f pos, int rowIndex) {
	float spacing = 8.0f;
	float tileWidth = 32.0f;
	float widthPerTile = tileWidth + spacing;
	int index = rowIndex * 9;
	for(int j = 0; j < 9; j++) {
		int i = index + j;
		SItemStack *itemStack = GetItemStack(i);
		CVector2f tilePos = CVector2f(pos.x + (float)j * widthPerTile, pos.y);
		graphics->DrawTilesheet(tilesheet, tilePos, 16, 16, 16, 64, 64, tileWidth, tileWidth);
		if(itemStack && itemStack->item) {
			DrawItemStackTile(tilePos, itemStack);
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

bool CInventory::AddItem(int id, int count) {
	for(int i = 0; i < size; i++) {
		if(items[i]) {
			if(items[i]->item->GetID() == id) {
				items[i]->count += count;
				return true;
			}
		}
	}

	for(int i = 0; i < size; i++) {
		if(items[i] == nullptr) {
			items[i] = new SItemStack();
			items[i]->count = count;
			items[i]->item = CItem::CreateFromID(owner, id);
			return true;
		}
	}

	return false;
}

CItem *CInventory::GetItem(int index) {
	ASSERT(index >= 0);
	ASSERT(index < size);

	if(items[index]) {
		return items[index]->item;
	} else {
		return nullptr;
	}
}

const CItem *CInventory::GetItem(int index) const {
	ASSERT(index >= 0);
	ASSERT(index < size);

	if(items[index]) {
		return items[index]->item;
	} else {
		return nullptr;
	}
}

SItemStack *CInventory::GetItemStack(int index)
{
	ASSERT(index >= 0);
	ASSERT(index < size);

	return items[index];
}

void CInventory::DecrementStack(int index)
{
	auto itemStack = GetItemStack(index);
	if(--itemStack->count <= 0) {
		delete itemStack->item;
		delete itemStack;
		items[index] = nullptr;
	}
}

void CInventory::RemoveItem(int index) {
	auto item = GetItem(index);
	if(item) {
		delete item;
		items[index] = nullptr;
	}
}

void CInventory::UseCurrentItem() {
	if(IsOpen()) {
		return;
	}

	if(items[currentSelected]) {
		bool clicked = false;
		if(items[currentSelected]->item->IsTool()) {
			clicked = input->GetMouseState().buttonMask & EMouseButton_LEFT;
		} else {
			clicked = input->GetMouseStateDelta().buttonMask & EMouseButton_LEFT;
		}

		if(clicked && items[currentSelected]->item->OnUse()) {
			DecrementStack(currentSelected);
		}
	}
}

void CInventory::SwitchOpen() {
	open = !open;
}

SItemStack *CInventory::GetCurrentSelectedItemStack() {
	return items[currentSelected];
}

void CInventory::DrawItemStackTile(const CVector2f &pos, SItemStack *itemStack)
{
	itemStack->item->Draw(pos);
	
	/* Do not display count when it is only one item */
	if(itemStack->count != 1) {
		graphics->DrawText(font, pos, CColor::white, StrUtl::FormatString("%d", itemStack->count));
	}
}