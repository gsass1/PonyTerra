#ifndef GAME_H
#define GAME_H

#include "IGame.h"
#include "Rect.h"

enum class EGameState {
	NONE = 0,
	MENU,
	INGAME,
};

class CGame : public IGame {
public:
				CGame();
				~CGame();

	void		Initialize();
	void		Quit();

	const char *GetGameName();

	void		PreloadMenuData();
	void		ReleaseMenuData();

	void		Update(float dtTime);
	void		Draw();

	CRect		GetViewRect() const;

	EGameState	gameState;
};

extern CGame game_local;

#endif
