#include "Item_HealthPotion.h"
#include "IResourceManager.h"
#include "Entity.h"
#include "Component_Attributes.h"
#include "IGraphics.h"

CItem_HealthPotion::CItem_HealthPotion(CEntity *owner) : CItem(owner) {
}

void CItem_HealthPotion::Initialize() {
	tilesheet = resMgr->GetTexture("data/res/tex/tilesheet.png");
}

void CItem_HealthPotion::OnUse() {
	auto attributes = GetComponent<CComponent_Attributes>(owner);
	if(attributes) {
		attributes->UseHealth(20);
	}
}

void CItem_HealthPotion::Draw(CVector2f pos) {
	graphics->DrawTilesheet(tilesheet, pos, 32, 16, 16, 64, 64, 32.0f, 32.0f);
}