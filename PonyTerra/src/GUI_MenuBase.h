#ifndef GUI_MENUBASE_H
#define GUI_MENUBASE_H

#include "Widget_Button.h"
#include "Vector2.h"
#include "GUI.h"
#include <vector>

class ITexture;

struct SCloudEntity
{
	CVector2f pos;
	CVector2f vel;
	float width;
	float height;

	SCloudEntity(CVector2f pos, CVector2f vel, float width, float height)
	{
		this->pos = pos;
		this->vel = vel;
		this->width = width;
		this->height = height;
	}
};

class CGUI_MenuBase {
public:
	CGUI_MenuBase();
	~CGUI_MenuBase();

	void		Initialize();
	void		Dispose();

	void		Update(float dtTime);
	void		Draw();

private:
	CWidget_Button *btWebsite;
	ITexture *	cloud;
	std::vector<SCloudEntity *> cloudEntities;

	void AddRandomCloud();
};

extern CGUI_MenuBase menuBase;

#endif