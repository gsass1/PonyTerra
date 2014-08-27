#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <vector>

class IGUI;

IGUI *GetGUI(const char *name);

class CGUIManager {
public:
					CGUIManager();
					~CGUIManager();
	
	void			Initialize();
    void            ClearStack();

	void			Push(IGUI *gui);
	void			Pop();

	void			Update(float dtTime);
	void			Draw();

	IGUI *			Current();
	unsigned int	GetStackSize() const;

private:
	std::vector<IGUI *> guiStack;
};

extern CGUIManager guiManager;

#endif