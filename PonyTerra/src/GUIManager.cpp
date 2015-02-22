#include "ICommon.h"
#include "GUI.h"
#include "GUIManager.h"
#include "GUI_IngameMenu.h"
#include "GUI_Loading.h"
#include "GUI_MenuFront.h"
#include "GUI_NewWorld.h"
#include "GUI_MenuBase.h"
#include "IGraphics.h"
#include "Game.h"
#include "GUI_Credits.h"

#include <string.h>

#include "IResourceManager.h"

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

	staticGUIs[4] = new CGUI_Credits();
	staticGUIs[4]->Initialize();
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

	if(strcmp(name, "Credits") == 0) {
		return staticGUIs[4];
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
	menuBase.Initialize();
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
	menuBase.Update(dtTime);

	if (guiStack.size() != 0) {
		guiStack.back()->Update(dtTime);
	}
}

void CGUIManager::Draw() {
	if (guiStack.size() != 0) {
		if(game_local.gameState == EGameState::MENU) {
			menuBase.Draw();
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
