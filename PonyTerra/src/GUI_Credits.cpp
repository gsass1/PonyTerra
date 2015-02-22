#include "GUI_Credits.h"
#include "IResourceManager.h"
#include "ICommon.h"
#include "IGraphics.h"
#include "GUIManager.h"

#define TRANSITION_TIME 2000

CGUI_Credits::CGUI_Credits()
{
	nukesoftwareLogo = nullptr;
	lastTicks = 0;
	stage = 0;
}

CGUI_Credits::~CGUI_Credits()
{
}

void CGUI_Credits::Initialize()
{
	nukesoftwareLogo = resMgr->GetTexture("data/res/tex/nukesoftwarelogo.png");
	lastTicks = common->GetTicks();
}

void CGUI_Credits::Dispose()
{
}

void CGUI_Credits::OnResize()
{
}

void CGUI_Credits::Update(float dtTime)
{
	if(common->GetTicks() - lastTicks > TRANSITION_TIME) {
		stage++;
		lastTicks = common->GetTicks();
		if(stage == 3) {
			guiManager.Push(GetGUI("MenuFront"));
		}
	}
}

void CGUI_Credits::Draw()
{
	byte overlayAlpha = 255;

	graphics->DrawRect(CRect(CVector2f(), graphics->GetWidth(), graphics->GetHeight()), CColor(0, 0, 0));
	graphics->DrawTexture(nukesoftwareLogo, CVector2f(graphics->GetSize().x / 2 - 250, graphics->GetSize().y / 2 - 65.0f), CVector2f(500, 125));

	if(stage == 0) {
		/* Blend in */
		overlayAlpha = 255 - (byte)(((float)common->GetTicks() - (float)lastTicks) / (float)TRANSITION_TIME * 255.0f);
	} else if(stage == 1) {
		/* Visible */
		overlayAlpha = 0;
	} else if(stage == 2) {
		/* Blend out */
		overlayAlpha = (byte)(((float)common->GetTicks() - (float)lastTicks) / (float)TRANSITION_TIME * 255.0f);
	}
	graphics->DrawRect(CRect(CVector2f(), graphics->GetWidth(), graphics->GetHeight()), CColor(0, 0, 0, overlayAlpha));
}