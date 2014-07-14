#include "IGraphics.h"
#include "GUIManager.h"
#include "GUI_NewWorld.h"
#include "Level.h"
#include "IResourceManager.h"
#include "ITexture.h"
#include "Widget_Button.h"

CGUI_NewWorld::CGUI_NewWorld() {
	bg = nullptr;
	btSmallWorld = new CWidget_Button("Small World (2000x1200)", CVector2f((float)graphics->GetWidth() / 2.0f, 380.0f));
	btMediumWorld = new CWidget_Button("Medium World (4200x1200)", CVector2f((float)graphics->GetWidth() / 2.0f, 320.0f));
	btBigWorld = new CWidget_Button("Big World (6000x2000)", CVector2f((float)graphics->GetWidth() / 2.0f, 260.0f));
	btBack = new CWidget_Button("Back", CVector2f((float)graphics->GetWidth() / 2.0f, 200.0f));
}

CGUI_NewWorld::~CGUI_NewWorld() {
	delete btSmallWorld;
	delete btMediumWorld;
	delete btBigWorld;
	delete btBack;
}

void CGUI_NewWorld::Initialize() {
	bg = resMgr->GetTexture("data/res/tex/menu_bg.png");

	btSmallWorld->Initialize();
	btMediumWorld->Initialize();
	btBigWorld->Initialize();
	btBack->Initialize();
}

void CGUI_NewWorld::Dispose() {
}

void CGUI_NewWorld::OnResize() {
	btSmallWorld->GetPos().Set((float)graphics->GetWidth() / 2.0f, 380.0f);
	btMediumWorld->GetPos().Set((float)graphics->GetWidth() / 2.0f, 320.0f);
	btBigWorld->GetPos().Set((float)graphics->GetWidth() / 2.0f, 260.0f);
	btBack->GetPos().Set((float)graphics->GetWidth() / 2.0f, 200.0f);
}

void CGUI_NewWorld::Update(float dtTime) {
	btSmallWorld->Update(dtTime);
	btMediumWorld->Update(dtTime);
	btBigWorld->Update(dtTime);
	btBack->Update(dtTime);

	if(btSmallWorld->IsClicked()) {
		guiManager.Push(GetGUI("Loading"));

		level.width = 1000;
		level.height = 1000;
		levelGenerate.StartGenerating();
	}

	if(btBack->IsClicked()) {
		guiManager.Pop();
	}
}

void CGUI_NewWorld::Draw() {
	graphics->DrawTexture(bg, CVector2f(0.0f, 0.0f));

	btSmallWorld->Draw();
	btMediumWorld->Draw();
	btBigWorld->Draw();
	btBack->Draw();
}
