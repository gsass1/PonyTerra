#ifndef GUI_LOADING_H
#define GUI_LOADING_H

#include "GUI.h"
#include <mutex>

class IFont;
class ITexture;

class CGUI_Loading : public IGUI {
public:
				CGUI_Loading();
				~CGUI_Loading();

	void		Initialize();
	void		Dispose();

	void		OnResize();

	void		Update(float dtTime);
	void		Draw();

	void		SetStatusText(const char *text);
	const char *GetStatusText();

private:
	IFont *		font;
	ITexture *	bgTex;

	char		statusText[256];
	std::mutex	statusTextSetMtx;
};

#endif
