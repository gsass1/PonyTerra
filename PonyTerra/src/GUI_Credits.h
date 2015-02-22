#ifndef GUI_CREDITS_H
#define GUI_CREDITS_H

#include "GUI.h"

class ITexture;

class CGUI_Credits : public IGUI {
public:
	CGUI_Credits();
	~CGUI_Credits();

	void		Initialize();
	void		Dispose();

	void		OnResize();

	void		Update(float dtTime);
	void		Draw();

private:
	ITexture *nukesoftwareLogo;

	unsigned int lastTicks;
	unsigned int stage;
};

#endif
