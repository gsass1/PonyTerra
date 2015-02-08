#include "Item_Tile.h"
#include "IGraphics.h"
#include "IResourceManager.h"
#include "Cursor.h"
#include "Level.h"
#include "Game.h"

CItem_Tile::CItem_Tile(CEntity *owner, int tileID) : CItem(owner), tileID(tileID)
{
	tilesheet = nullptr;
}

void CItem_Tile::Initialize()
{
	tilesheet = resMgr->GetTexture("data/res/tex/tilesheet.png");
}

bool CItem_Tile::OnUse()
{
	if(cursor.currentSelectedTile && (cursor.currentSelectedTile->type == ETileType::AIR)) {
		if(level.GetNeighborTileDirections(cursor.currentSelectedTile->x / TILE_SIZE, cursor.currentSelectedTile->y / TILE_SIZE)) {
			cursor.currentSelectedTile->type = (ETileType)tileID;
			return true;
		}
	}
	return false;
}

void CItem_Tile::Update(float dtTime)
{

}

void CItem_Tile::Draw(CVector2f pos)
{
	graphics->DrawTilesheet(tilesheet, pos, tileID, 16, 16, 64, 64, 32.0f, 32.0f);
}

std::string CItem_Tile::GetName() const
{
	return std::string("Tile ID: ") + std::to_string(tileID);
}