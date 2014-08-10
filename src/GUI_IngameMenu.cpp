#include "GUI_IngameMenu.h"
#include "Color.h"
#include "IFont.h"
#include "IGraphics.h"
#include "GUI_Loading.h"
#include "MutexLock.h"
#include "IResourceManager.h"
#include "ITexture.h"
#include "Widget_Button.h"
#include <string.h>
#include "Game.h"

CGUI_IngameMenu::CGUI_IngameMenu() {
    bgTex = nullptr;
    font = nullptr;
    btResume = new CWidget_Button("Resume", CVector2f((float)graphics->GetWidth() / 2.0f, 480.0f));
    btExit = new CWidget_Button("Exit", CVector2f((float)graphics->GetWidth() / 2.0f, 380.0f));
}

CGUI_IngameMenu::~CGUI_IngameMenu() {
}

void CGUI_IngameMenu::Initialize() {
    bgTex = resMgr->GetTexture("data/res/tex/menu_bg.png");
    font = resMgr->GetFont("data/res/font/menu.fnt");
    btResume->Initialize();
    btExit->Initialize();
}

void CGUI_IngameMenu::Dispose() {
}

void CGUI_IngameMenu::OnResize() {
}

void CGUI_IngameMenu::Update(float dtTime) {
    btResume->Update(dtTime);
    btExit->Update(dtTime);

    if(btResume->IsClicked()) {
        game_local.ToggleShowIngameMenu();
    }

    if(btExit->IsClicked()) {
        game_local.ToggleShowIngameMenu();
        game_local.UnloadLevel();
    }
}

void CGUI_IngameMenu::Draw() {
    graphics->DrawRect(CRect(0.0f, graphics->GetWidth(), graphics->GetHeight()), CColor(0, 0, 0, 128));
    btResume->Draw();
    btExit->Draw();
}
