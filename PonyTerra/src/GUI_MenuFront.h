#ifndef GUI_MENUFRONT_H
#define GUI_MENUFRONT_H

#include "GUI.h"

class ITexture;
class CWidget_Button;

class CGUI_MenuFront : public IGUI {
public:
                CGUI_MenuFront();
                ~CGUI_MenuFront();

    void        Initialize();
    void        Dispose();

    void        OnResize();

    void        Update(float dtTime);
    void        Draw();

private:
    ITexture *  bg;

    CWidget_Button *btNewWorld;
    CWidget_Button *btLoadWorld;
    CWidget_Button *btOptions;
    CWidget_Button *btExit;
};

#endif