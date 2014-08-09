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
    void        UpdateMenu(float dtTime);
    void        UpdateGame(float dtTime);

	void		Draw();
    void        DrawMenu();
    void        DrawGame();

	CEntity *	GetPlayerEntity() const;

	void		LookAt(const CRect &rect);
	CRect		GetViewRect() const;

	EGameState	gameState;

private:
	CRect		viewRect;
	CEntity *	playerEntity;
};

extern CGame game_local;

#endif
