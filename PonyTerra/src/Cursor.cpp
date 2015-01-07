#include "Cursor.h"
#include "Game.h"
#include "IInput.h"
#include "Level.h"
#include "IGraphics.h"

CCursor cursor;

CCursor::CCursor()
{
	currentSelectedTile = nullptr;
}

CCursor::~CCursor()
{
}

void CCursor::Initialize()
{
}

void CCursor::Update(float dtTime)
{
	auto mouseState = input->GetMouseState();

	pos.x = (float)mouseState.x;
	pos.y = (float)mouseState.y;

	auto inWorldSpace = game_local.ToWorldSpace(pos);
	auto tile = level.GetTileInWorldSpace(inWorldSpace);

	if(tile) {
		currentSelectedTile = tile;
		currentSelectedTilePos.x = tile->x / TILE_SIZE;
		currentSelectedTilePos.y = tile->y / TILE_SIZE;
	} else {
		currentSelectedTile = nullptr;
	}
}

void CCursor::DrawTileHighlight()
{
	if(currentSelectedTile) {
		graphics->DrawRect(CRect(game_local.ToScreenSpace(CVector2f((float)currentSelectedTile->x, (float)currentSelectedTile->y)), TILE_SIZE, TILE_SIZE), CColor(255, 255, 255, 128));
	}
}