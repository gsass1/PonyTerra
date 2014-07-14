#ifndef LEVEL_H
#define LEVEL_H

#include "MutexLock.h"
#include "Vector2.h"
#include <thread>

//--------------------------------------------------

#define TILE_SIZE 64

#define SMALL_WORLD_SIZE_W 2000
#define SMALL_WORLD_SIZE_H 1200

#define MEDIUM_WORLD_SIZE_W 4200
#define MEDIUM_WORLD_SIZE_H 1200

#define BIG_WORLD_SIZE_W 6000
#define BIG_WORLD_SIZE_H 2000

//--------------------------------------------------

enum class ETileType
{
	AIR = 0,
	DIRT,
};

//--------------------------------------------------

class CTile
{
public:
	int x;
	int y;

	ETileType type;

	CTile(int x, int y, ETileType type) {
		this->x = x;
		this->y = y;
		this->type = type;
	}

	CVector2f GetPosition() const {
		return CVector2f((float)x, (float)y);
	}
};

//--------------------------------------------------

class CLevelGenerate
{
public:
	CLevelGenerate() { isGenerating = false; }

	void StartGenerating();

	bool IsGenerating() const { return isGenerating; }

	std::mutex stateLock;
	bool isGenerating;
};

extern CLevelGenerate levelGenerate;

// The Level Generation thread
extern std::thread *levelGenThread;

//--------------------------------------------------

class ITexture;

class CLevel
{
public:
				CLevel();
				~CLevel();

	void		Initialize();

	void		Load(const char *filepath);
	void		Generate(int width, int height);
	
	bool		IsLoaded() const;

	void		Draw();

	bool		IsCollidingWithTiles(const CRect &rect);

	int			width;
	int			height;

private:
	friend class CLevelGenerate;

	ITexture *	tilesheetTex;

	/* Holds all tiles */
	CTile ***	tileData;

	double		time;
	bool		isBossSummoned;

	bool		isLoaded;

	CVector2f	spawnPos;

	void		AllocTileData();
	void		DisposeTileData();

	void		SetLoadingText(const char * text);
};

extern CLevel level;

#endif
