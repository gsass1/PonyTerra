#include "Game.h"
#include "ICommon.h"

#ifdef STANDALONE

#define GAMEAPI

#else
#ifdef _WIN32

#ifdef PONYTERRA_EXPORTS

#define GAMEAPI __declspec(dllexport)

#else

#define GAMEAPI __declspec(dllimport)

#endif

#else

#define GAMEAPI

#endif

#endif

#ifndef STANDALONE
IConfig *config;
ICommon *common;
IFileSystem *fileSystem;
IGame *game;
IGraphics *graphics;
IInput *input;
IResourceManager *resMgr;
ISoundSystem *soundSystem;
#endif

extern "C" GAMEAPI void GameDLLExchange(EngineGlobals *eg, GameGlobals *gg) {
#ifndef STANDALONE
	::config = eg->config;
	::common = eg->common;
	::fileSystem = eg->filesystem;
	::game = &game_local;
	::graphics = eg->graphics;
	::input = eg->input;
	::resMgr = eg->resMgr;
	::soundSystem = eg->soundSys;
#endif
	gg->game = &game_local;
}