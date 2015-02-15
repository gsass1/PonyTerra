#include "Item_Spellbook.h"
#include "IResourceManager.h"
#include "IGraphics.h"
#include "Entity.h"
#include "Component_Attributes.h"

CItem_Spellbook::CItem_Spellbook(CEntity *owner) : CItem(owner)
{
	tilesheet = nullptr;
}

CItem_Spellbook::~CItem_Spellbook()
{
}

void CItem_Spellbook::Initialize()
{
	tilesheet = resMgr->GetTexture("/data/tex/tilesheet.png");
	attributes = GetComponent<CComponent_Attributes>(owner);
}

void CItem_Spellbook::Update(float dtTime)
{
}

bool CItem_Spellbook::OnUse()
{
	if(attributes->UseMana(20)) {
		/* TODO: fire projectile */
	}
	return false;
}

void CItem_Spellbook::Draw(CVector2f pos)
{
	/* TODO: Replace with real texture */
	graphics->DrawTilesheet(tilesheet, pos, 32, 16, 16, 64, 64, 32.0f, 32.0f);
}