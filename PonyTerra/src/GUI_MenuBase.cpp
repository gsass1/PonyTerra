#include "GUI_MenuBase.h"
#include "IResourceManager.h"
#include "IGraphics.h"

#ifdef _WIN32 
#include <Windows.h>
#include <shellapi.h>
#endif

CGUI_MenuBase menuBase;

CGUI_MenuBase::CGUI_MenuBase()
{
	cloud = nullptr;
}

CGUI_MenuBase::~CGUI_MenuBase()
{
	for(auto entity : cloudEntities) {
		delete entity;
	}
}

void CGUI_MenuBase::Initialize()
{
	btWebsite = new CWidget_Button("www.nukesoftware.de", CVector2f((float)graphics->GetWidth() / 2.0f, 32.0f));
	btWebsite->Initialize();

	cloud = resMgr->GetTexture("data/res/tex/cloud.png");

	for(int i = 0; i < Math::Random(5) + 2; i++) {
		AddRandomCloud();
	}
}

void CGUI_MenuBase::Dispose()
{
}

void CGUI_MenuBase::Update(float dtTime)
{
	btWebsite->Update(dtTime);

#ifdef _WIN32 
	if(btWebsite->IsClicked()) {
		ShellExecute(0, 0, "https://www.nukesoftware.de", 0, 0, SW_SHOW);
	}
#endif

	for(auto entity : cloudEntities) {
		entity->pos += entity->vel * dtTime;

		if(entity->pos.x > graphics->GetSize().x + entity->width) {
			entity->pos.x = -entity->width;
		} else if(entity->pos.x < -entity->width) {
			entity->pos.x = graphics->GetSize().x + entity->width;
		}
	}
}

void CGUI_MenuBase::Draw()
{
	graphics->DrawRect(CRect(CVector2f(), graphics->GetWidth(), graphics->GetHeight()), CColor(30, 100, 220));
	
	for(auto entity : cloudEntities) {
		graphics->DrawTexture(cloud, entity->pos, entity->width, entity->height);
	}

	btWebsite->Draw();
}

void CGUI_MenuBase::AddRandomCloud()
{
	int sizeDivisor = 2;
	cloudEntities.push_back(new SCloudEntity(CVector2f((float)Math::Random(graphics->GetSize().x)), CVector2f((float)Math::Random(100) - 50.0f, 0.0f), 1024 / sizeDivisor, 512 / sizeDivisor));
}
