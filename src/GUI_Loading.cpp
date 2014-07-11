#include "Color.h"
#include "IFont.h"
#include "IGraphics.h"
#include "GUI_Loading.h"
#include "MutexLock.h"
#include "IResourceManager.h"
#include "ITexture.h"

#include <string.h>

CGUI_Loading::CGUI_Loading() {
	bgTex = nullptr;
	font = nullptr;
	statusText[0] = '\0';
}

CGUI_Loading::~CGUI_Loading() {
}

void CGUI_Loading::Initialize() {
	bgTex = resMgr->GetTexture("data/res/tex/menu_bg.png");
	font = resMgr->GetFont("data/res/font/menu.fnt");
}

void CGUI_Loading::Dispose() {
}

void CGUI_Loading::OnResize() {
}

void CGUI_Loading::Update(float dtTime) {
}

void CGUI_Loading::SetStatusText(const char *text) {
	{
		CMutexLock lock(&statusTextSetMtx);
		strcpy(statusText, text);
	}
}

const char *CGUI_Loading::GetStatusText() {
	{
		CMutexLock lock(&statusTextSetMtx);
		return statusText;
	}
}

void CGUI_Loading::Draw() {
	graphics->DrawTexture(bgTex, CVector2f(0.0f, 0.0f));
	if(statusText[0] != '\0') {
        graphics->DrawText(font, graphics->GetSize() / 2.0f, CColor(128, 128, 128), statusText, true);
	}
}
