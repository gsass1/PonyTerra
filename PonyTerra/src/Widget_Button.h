#ifndef WIDGET_BUTTON_H
#define WIDGET_BUTTON_H

#include "Widget.h"

class IFont;

class CWidget_Button : public CWidget {
public:
					CWidget_Button(const char *text, CVector2f pos);
					~CWidget_Button();

	void			Initialize();

	void			Update(float dtTime);
	void			Draw();

	CRect			GetRect() const;

private:
	const IFont *	font;
	char			text[256];
};

#endif