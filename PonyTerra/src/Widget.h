#ifndef WIDGET_H
#define WIDGET_H

#include "Rect.h"
#include "Vector2.h"

/* Base class for interacting GUI elements */
class CWidget {
public:
					CWidget(CVector2f pos, int width, int height);
	virtual			~CWidget() {}

	virtual void	Initialize() = 0;

	virtual void	Update(float dtTime);
	virtual void	Draw() = 0;

	bool			IsMouseHovered() const;

	bool			IsClicked() const;

	virtual CRect	GetRect() const { return CRect(pos, width, height); }

	CVector2f		GetPos() const { return pos; }
	CVector2f &		GetPos() { return pos; }

protected:
	CVector2f		pos;
	int				width;
	int				height;

	bool			isMouseHovered;
	bool			isClicked;
};

#endif