#include "Color.h"
#include "ICommon.h"
#include "IFont.h"
#include "IGraphics.h"
#include "GUIManager.h"
#include "GUI_MenuFront.h"
#include "Level.h"
#include "IResourceManager.h"
#include "ITexture.h"
#include "Widget_Button.h"
#include "IInput.h"
#include "Game.h"

CGUI_MenuFront::CGUI_MenuFront() {
	bg = nullptr;
	titleFont = nullptr;
	btNewWorld = new CWidget_Button("New World",
		CVector2f((float)graphics->GetWidth() / 2.0f, 380.0f));

	btLoadWorld = new CWidget_Button("Load World",
		CVector2f((float)graphics->GetWidth() / 2.0f, 320.0f));

	btOptions = new CWidget_Button("Options",
		CVector2f((float)graphics->GetWidth() / 2.0f, 260.0f));

	btExit = new CWidget_Button("Exit",
		CVector2f((float)graphics->GetWidth() / 2.0f, 220.0f));
}

CGUI_MenuFront::~CGUI_MenuFront() {
	delete btNewWorld;
	delete btLoadWorld;
	delete btOptions;
	delete btExit;
}

void CGUI_MenuFront::Initialize() {
	bg = resMgr->GetTexture("data/res/tex/menu_bg.png");
	titleFont = resMgr->GetFont("data/res/font/title.fnt");

	btNewWorld->Initialize();
	btLoadWorld->Initialize();
	btOptions->Initialize();
	btExit->Initialize();
}

void CGUI_MenuFront::Dispose() {
}

void CGUI_MenuFront::OnResize() {
	btNewWorld->GetPos().Set((float)graphics->GetWidth() / 2.0f, 380.0f);
	btLoadWorld->GetPos().Set((float)graphics->GetWidth() / 2.0f, 320.0f);
	btOptions->GetPos().Set((float)graphics->GetWidth() / 2.0f, 260.0f);
	btExit->GetPos().Set((float)graphics->GetWidth() / 2.0f, 220.0f);
}

void CGUI_MenuFront::Update(float dtTime) {
	btNewWorld->Update(dtTime);
	btLoadWorld->Update(dtTime);
	btOptions->Update(dtTime);
	btExit->Update(dtTime);

	if(input->KeyPressed(NSKey::NSK_ESCAPE, true)) {
		common->Quit();
	}

	if(btNewWorld->IsClicked()) {
		guiManager.Push(GetGUI("NewWorld"));
	}

	if(btLoadWorld->IsClicked()) {
		game_local.LoadLevel("noname");
	}

	if(btExit->IsClicked()) {
		common->Quit();
	}
}

void CGUI_MenuFront::Draw() {
	graphics->DrawText(titleFont, CVector2f(graphics->GetSize().x / 2.0f, graphics->GetSize().y - titleFont->GetTextSize("PonyTerra").y - 64.0f), CColor::white, "PonyTerra", true);

	btNewWorld->Draw();
	btLoadWorld->Draw();
	btOptions->Draw();
	btExit->Draw();
}
