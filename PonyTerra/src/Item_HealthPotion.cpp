#include "Item_HealthPotion.h"
#include "IResourceManager.h"
#include "Entity.h"
#include "Component_Attributes.h"
#include "IGraphics.h"
#include "ICommon.h"

CItem_HealthPotion::CItem_HealthPotion(CEntity *owner) : CItem(owner) {
	animState = 0;
	lastTicks = 0;
}

void CItem_HealthPotion::Initialize() {
	tilesheet = resMgr->GetTexture("data/res/tex/tilesheet.png");
}

bool CItem_HealthPotion::OnUse() {
	auto attributes = GetComponent<CComponent_Attributes>(owner);
	if(attributes) {
		return attributes->UseHealth(20);
	}

	return false;
}

void CItem_HealthPotion::Update(float dtTime)
{
	if(common->GetTicks() - lastTicks > 250) {
		if(++animState == 4) {
			animState = 0;
		}
		lastTicks = common->GetTicks();
	}
}

void CItem_HealthPotion::Draw(CVector2f pos) {
	graphics->DrawTilesheet(tilesheet, pos, 32 + animState, 16, 16, 64, 64, 32.0f, 32.0f);
}