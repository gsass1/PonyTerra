#ifndef GAME_H
#define GAME_H

#include "IGame.h"
#include "Entity.h"
#include "Rect.h"
#include "IInput.h"

class IFile;

class ISaveable
{
public:
    virtual ~ISaveable() {}

    virtual void Load(IFile *file) = 0;
    virtual void Save(IFile *file) = 0;
};

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

    void        BeginLevelGenProccess(int levelWidth, int levelHeight);
    void        UnloadLevel();
    void        LoadLevel(const std::string &filepath);
    void        SaveLevel(const std::string &filepath);
    void        SaveLevelAndExit(const std::string &filepath);

    void        ToggleShowIngameMenu();

    bool        KeyPressedIngame(NSKey key, bool once = false);

	EGameState	gameState;

private:
	CRect		viewRect;
	CEntity *	playerEntity;
    bool        showIngameMenu;
};

extern CGame game_local;

#endif
