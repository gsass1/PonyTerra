#ifndef GUI_NEWWORLD_H
#define GUI_NEWWORLD_H

#include "GUI.h"

class ITexture;
class CWidget_Button;

class CGUI_NewWorld : public IGUI {
public:
                CGUI_NewWorld();
                ~CGUI_NewWorld();

    void        Initialize();
    void        Dispose();

    void        OnResize();

    void        Update(float dtTime);
    void        Draw();

private:
    ITexture *  bg;

    CWidget_Button *btSmallWorld;
    CWidget_Button *btMediumWorld;
    CWidget_Button *btBigWorld;

    CWidget_Button *btBack;
};

#endif