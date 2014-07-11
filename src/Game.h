#ifndef GAME_H
#define GAME_H

#include "IGame.h"
#include "Entity.h"
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

	void		InitializeGame();

	void		Quit();

	const char *GetGameName();

	void		PreloadMenuData();
	void		ReleaseMenuData();

	void		Update(float dtTime);
	void		Draw();

	CEntity *	GetPlayerEntity() const;

	CRect		GetViewRect() const;

	EGameState	gameState;

private:
	CEntity *	playerEntity;
};

extern CGame game_local;

#endif
