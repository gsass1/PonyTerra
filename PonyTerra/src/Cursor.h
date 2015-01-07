#ifndef CURSOR_H
#define CURSOR_H

#include "Vector2.h"

class CTile;

class CCursor
{
public:
				CCursor();
				~CCursor();

	void		Initialize();

	void		Update(float dtTime);
	void		DrawTileHighlight();

	CTile *		currentSelectedTile;
	CVector2f	pos;
};

extern CCursor cursor;

#endif