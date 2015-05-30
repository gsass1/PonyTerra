#include "Item_Spellbook.h"
#include "IResourceManager.h"
#include "IGraphics.h"
#include "Entity.h"
#include "Component_Attributes.h"
#include "Component_Physical.h"
#include "EntityFactory.h"
#include "EntityManager.h"
#include "IInput.h"
#include "Game.h"

CItem_Spellbook::CItem_Spellbook(CEntity *owner) : CItem(owner)
{
	tilesheet = nullptr;
}

CItem_Spellbook::~CItem_Spellbook()
{
}

void CItem_Spellbook::Initialize()
{
	tilesheet = resMgr->GetTexture("data/res/tex/tilesheet.png");
	attributes = GetComponent<CComponent_Attributes>(owner);
}

void CItem_Spellbook::Update(float dtTime)
{
}

bool CItem_Spellbook::OnUse()
{
	if(true) {
	//if(attributes->UseMana(20)) {
		/* TODO: fire projectile */
		CVector2f pos = GetComponent<CComponent_Physical>(owner)->rect.pos;
		auto ms = input->GetMouseState();
		CVector2f mousePos = game_local.ToWorldSpace(CVector2f((float)ms.x, (float)ms.y));
		float angle = atan2f(mousePos.x - pos.x, mousePos.y - pos.y);
		float xv = Math::Sinf(angle);
		float yv = Math::Cosf(angle);
		auto proj = entityFactory.CreateSpellbookProjectile(owner, pos, CVector2f(xv, yv));
		entityMgr.AddEntity(proj);
	}
	return false;
}

void CItem_Spellbook::Draw(CVector2f pos)
{
	/* TODO: Replace with real texture */
	graphics->DrawTilesheet(tilesheet, pos, 32, 16, 16, 64, 64, 32.0f, 32.0f);
}