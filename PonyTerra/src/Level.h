#ifndef LEVEL_H
#define LEVEL_H

#include "MutexLock.h"
#include "Vector2.h"
#include <thread>
#include <atomic>

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
    GRASS,
};

//--------------------------------------------------

class CTile
{
public:
	int x;
	int y;

	ETileType type;

    int flags;

    CTile()
    {
        x = 0;
        y = 0;
        flags = 0;
        type = ETileType::AIR;
    }

	CTile(int x, int y, ETileType type)
    {
		this->x = x;
		this->y = y;
		this->type = type;
	}

	CVector2f GetPosition() const
    {
		return CVector2f((float)x, (float)y);
	}
};



//--------------------------------------------------

extern std::string levelFilename;

enum class ELevelProcessType
{
    NONE,
    GENERATE,
    UNLOAD,
    SAVE,
    SAVE_UNLOAD,
    LOAD,
    UNLOAD_LOAD,
};

class CLevelProcess
{
public:
    CLevelProcess() { processType = ELevelProcessType::NONE; curStatusPerc = 0.0; finishSignal = false;  }

    void StartProcess(ELevelProcessType type);

    ELevelProcessType StopThreadIfFinished();

    void SetStatus(ELevelProcessType type) {
        CMutexLock lock(&statusLock);
        processType = type;
    }

    ELevelProcessType GetStatus() {
        CMutexLock lock(&statusLock);
        return processType;
    }

    bool finishSignal;
	std::mutex statusLock;
    std::thread *thread;
    ELevelProcessType processType;
    double curStatusPerc;
};

extern CLevelProcess levelProcess;

//--------------------------------------------------

class ITexture;

class CLevel
{
public:
				CLevel();
				~CLevel();

	void		Initialize();

    void        Clear();

	void		Load(const char *filepath);

    void        Save(const char *filepath);

	void		Generate(int width, int height);

    bool        PlaceGrass(int x, int y);
	
	bool		IsLoaded() const;

	void		Draw();

	bool		IsCollidingWithTiles(const CRect &rect);

	CTile *		GetTile(int x, int y);
	CTile *		GetTileInWorldSpace(const CVector2f &pos);

	void		RemoveTileInWorldSpace(const CVector2f &pos);
	void		RemoveTile(int x, int y);
	void		RemoveTile(CTile *tile);

	int			width;
	int			height;

private:
	friend class CLevelGenerate;

	ITexture *	tilesheetTex;

    CTile *tileMemPool;

	double		time;
	bool		isBossSummoned;

	bool		isLoaded;

	CVector2f	spawnPos;

	void		AllocTileData();
	void		DisposeTileData();

	void		SetLoadingText(const char * text, double perc = 0.0);
};

extern CLevel level;

#endif
