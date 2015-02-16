#include "ICommon.h"
#include "GUI.h"
#include "GUIManager.h"
#include "GUI_IngameMenu.h"
#include "GUI_Loading.h"
#include "GUI_MenuFront.h"
#include "GUI_NewWorld.h"
#include "IGraphics.h"
#include "Game.h"

#include <string.h>

CGUIManager guiManager;

namespace
{

IGUI **staticGUIs;

void InitStaticGUIs() {
	staticGUIs = new IGUI*[32];

	staticGUIs[0] = new CGUI_MenuFront();
	staticGUIs[0]->Initialize();

	staticGUIs[1] = new CGUI_NewWorld();
	staticGUIs[1]->Initialize();

	staticGUIs[2] = new CGUI_Loading();
	staticGUIs[2]->Initialize();

    staticGUIs[3] = new CGUI_IngameMenu();
    staticGUIs[3]->Initialize();
}

}

IGUI *GetGUI(const char *name) {
	if(strcmp(name, "MenuFront") == 0) {
		return staticGUIs[0];
	}

	if(strcmp(name, "NewWorld") == 0) {
		return staticGUIs[1];
	}

	if(strcmp(name, "Loading") == 0) {
		return staticGUIs[2];
	}

    if(strcmp(name, "IngameMenu") == 0) {
        return staticGUIs[3];
    }

    ASSERT(false);

	return NULL;
}

CGUIManager::CGUIManager() {
}

CGUIManager::~CGUIManager() {
}

void CGUIManager::Initialize() {
	InitStaticGUIs();
}

void CGUIManager::ClearStack()
{
    guiStack.clear();
}

void CGUIManager::Push(IGUI *gui) {
	guiStack.push_back(gui);
}

void CGUIManager::Pop() {
	ASSERT(guiStack.size() != 0);
	guiStack.pop_back();
}

void CGUIManager::Update(float dtTime) {
	if (guiStack.size() != 0) {
		guiStack.back()->Update(dtTime);
	}
}

void CGUIManager::Draw() {
	if (guiStack.size() != 0) {
		if(!game_local.IsShowingIngameMenu()) {
			/* TODO: draw background animation, put this code somewhere else */
			graphics->DrawRect(CRect(CVector2f(), graphics->GetWidth(), graphics->GetHeight()), CColor(30, 100, 220));
		}
		guiStack.back()->Draw();
	}
}

IGUI *CGUIManager::Current() {
	ASSERT(guiStack.size() != 0);
	return guiStack.back();
}

unsigned int CGUIManager::GetStackSize() const {
	return guiStack.size();
}
