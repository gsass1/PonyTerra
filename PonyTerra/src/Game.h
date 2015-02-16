#ifndef GAME_H
#define GAME_H

#include "IGame.h"
#include "Entity.h"
#include "Rect.h"
#include "IInput.h"

#define TIME_DAY 10000.0f
#define TIME_NIGHT 10000.0f
#define TIME_TOTAL 20000.0f
#define TIME_PER_SECOND 166.6666f

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

    void        OnPrint(const char *msg);

	void		PreloadMenuData();
	void		ReleaseMenuData();

	void		Update(float dtTime);
    void        UpdateMenu(float dtTime);
    void        UpdateGame(float dtTime);

	void		Draw();
    void        DrawMenu();
    void        DrawGame();

	void		DrawTileHighlight();

	CEntity *	GetPlayerEntity() const;

	void		LookAt(const CRect &rect);
	CRect		GetViewRect() const;

    void        BeginLevelGenProccess(int levelWidth, int levelHeight);
    void        UnloadLevel();
    void        LoadLevel(const std::string &filepath);
    void        SaveLevel(const std::string &filepath);
    void        SaveLevelAndExit(const std::string &filepath);

    void        ToggleShowIngameMenu();
	bool		IsShowingIngameMenu() const { return showIngameMenu; }

    bool        KeyPressedIngame(NSKey key, bool once = false);

	CVector2f	ToScreenSpace(const CVector2f &pos) const;
	CVector2f	ToWorldSpace(const CVector2f &pos) const;

	EGameState	gameState;

	CEntity *	playerEntity;

	bool		showBoundingBoxes;

	float		time;

private:
	CRect		viewRect;
    bool        showIngameMenu;
};

extern CGame game_local;

#endif
