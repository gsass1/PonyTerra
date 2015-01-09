#ifndef ITEM_TILE_H
#define ITEM_TILE_H

#include "Item.h"

class ITexture;

class CItem_Tile : public CItem
{
public:
				CItem_Tile(CEntity *owner, int tileID);

	void		Initialize();
	bool		OnUse();

	void		Draw(CVector2f pos);

private:
	int			tileID;
	ITexture *	tilesheet;
};

#endif