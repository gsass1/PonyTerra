#ifndef GUI_INGAMEMENU_H
#define GUI_INGAMEMENU_H

#include "GUI.h"

class IFont;
class ITexture;
class CWidget_Button;

class CGUI_IngameMenu : public IGUI {
public:
				CGUI_IngameMenu();
				~CGUI_IngameMenu();

    void		Initialize();
    void		Dispose();

    void		OnResize();

    void		Update(float dtTime);
    void		Draw();

private:
    IFont *		font;
    ITexture *	bgTex;

    CWidget_Button *btResume;
    CWidget_Button *btExit;
};

#endif
