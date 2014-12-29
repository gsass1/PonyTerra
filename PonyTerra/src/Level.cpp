#include "ICommon.h"
#include "File.h"
#include "IFilesystem.h"
#include "Game.h"
#include "IGraphics.h"
#include "Level.h"
#include "NoiseGenerator.h"
#include "IResourceManager.h"
#include "ITexture.h"
#include "Component_Physical.h"

#include "MutexLock.h"

#include "GUIManager.h"
#include "GUI_Loading.h"

//--------------------------------------------------

CLevelProcess levelProcess;

std::string levelFilename;

static void ThreadBeginStartGenerating()
{
    level.Generate(level.width, level.height);

    {
        CMutexLock lock(&levelProcess.statusLock);
        levelProcess.finishSignal = true;
    }
}

static void ThreadBeginStartUnloading()
{
    level.Clear();

    {
        CMutexLock lock(&levelProcess.statusLock);
        levelProcess.finishSignal = true;
    }
}

static void ThreadBeginStartSaving()
{
    level.Save(levelFilename.c_str());

    {
        CMutexLock lock(&levelProcess.statusLock);
        levelProcess.finishSignal = true;
    }
}

static void ThreadBeginStartSaving_Unload()
{
    level.Save(levelFilename.c_str());
    level.Clear();

    {
        CMutexLock lock(&levelProcess.statusLock);
        levelProcess.finishSignal = true;
    }
}

static void ThreadBeginStartLoading()
{
    level.Load(levelFilename.c_str());

    {
        CMutexLock lock(&levelProcess.statusLock);
        levelProcess.finishSignal = true;
    }
}

static void ThreadBeginStartUnload_Load()
{
    level.Clear();
    level.Load(levelFilename.c_str());

    {
        CMutexLock lock(&levelProcess.statusLock);
        levelProcess.finishSignal = true;
    }
}

//--------------------------------------------------

void CLevelProcess::StartProcess(ELevelProcessType type)
{
    this->processType = type;
    if(type == ELevelProcessType::GENERATE) {
        thread = new std::thread(::ThreadBeginStartGenerating);
    } else if(type == ELevelProcessType::UNLOAD) {
        thread = new std::thread(::ThreadBeginStartUnloading);
    } else if(type == ELevelProcessType::SAVE) {
        thread = new std::thread(::ThreadBeginStartSaving);
    } else if(type == ELevelProcessType::SAVE_UNLOAD) {
        thread = new std::thread(::ThreadBeginStartSaving_Unload);
    } else if(type == ELevelProcessType::LOAD) {
        thread = new std::thread(::ThreadBeginStartLoading);
    } else if(type == ELevelProcessType::UNLOAD_LOAD) {
        thread = new std::thread(::ThreadBeginStartUnload_Load);
    }
}

ELevelProcessType CLevelProcess::StopThreadIfFinished()
{
    bool hasFinished;
    {
        CMutexLock lock(&levelProcess.statusLock);
        hasFinished = levelProcess.finishSignal;
    }

    if(hasFinished && levelProcess.GetStatus() != ELevelProcessType::NONE) {
        if(levelProcess.thread->joinable()) {
            levelProcess.thread->join();
            ELevelProcessType typeBefore = levelProcess.GetStatus();
            levelProcess.SetStatus(ELevelProcessType::NONE);
            levelProcess.finishSignal = false;
            return typeBefore;
        }
    }
    return ELevelProcessType::NONE;
}

//--------------------------------------------------

CLevel level;

CLevel::CLevel()
{
	width = height = 0;
	tilesheetTex = nullptr;
	tileMemPool = nullptr;
	time = 0;
	isBossSummoned = false;

	isLoaded = false;
}

CLevel::~CLevel()
{
}

void CLevel::Initialize()
{
	tilesheetTex = resMgr->GetTexture("data/res/tex/tilesheet.png");
}

void CLevel::Clear()
{
    DisposeTileData();
}

void CLevel::Load(const char *filepath)
{
	if(isLoaded) {
		common->Error("%s", "Cannot load new level while a level is already loaded!\n");
	}

	IFile *file = fileSystem->OpenFile(filepath, EFileMode::READ);

    ASSERT(file);

	width = file->ReadInt32();
	height = file->ReadInt32();

	if(!width || !height || width < 0 || height < 0) {
		common->Error("Corrupt Level File\n");
	}

	game_local.playerEntity->GetComponents()->Get<CComponent_Physical>()->rect.pos.x = file->ReadFloat();
	game_local.playerEntity->GetComponents()->Get<CComponent_Physical>()->rect.pos.y = file->ReadFloat();

	AllocTileData();

    SetLoadingText("Loading level");

    double perc = 0.0;

    for(int i = 0; i < width; i++) {

        perc = (double)i / (double)width;
        SetLoadingText("Loading tiles", perc);

        for(int j = 0; j < height; j++) {
            GetTile(i, j)->type = (ETileType)file->ReadInt32();
            GetTile(i, j)->flags = file->ReadInt32();
        }
    }

	isLoaded = true;
}

void CLevel::Save(const char *filepath)
{
    ASSERT(isLoaded);

    SetLoadingText("Saving level");

    IFile *file = fileSystem->OpenFile(filepath, EFileMode::WRITE);

    ASSERT(file);

    file->WriteInt32(width);
    file->WriteInt32(height);

	file->WriteFloat(GetComponent<CComponent_Physical>(game_local.playerEntity)->rect.pos.x);
	file->WriteFloat(GetComponent<CComponent_Physical>(game_local.playerEntity)->rect.pos.y);

    double perc = 0.0;

    for(int i = 0; i < width; i++) {

        perc = (double)i / (double)width;
        SetLoadingText("Saving tiles", perc);

        for(int j = 0; j < height; j++) {
            file->WriteInt32((int)GetTile(i, j)->type);
            file->WriteInt32(GetTile(i, j)->flags);
        }
    }
}

void CLevel::Generate(int width, int height)
{
	this->width = width;
	this->height = height;

	AllocTileData();

	CNoiseGenerator noiseGen;

	noiseGen.Set(16, 22, 0.085, 0.3);
	int groundLevel = 200;

	for (int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			if(y < groundLevel) {
				GetTile(x, y)->type = ETileType::DIRT;
			}
		}
	}

	SetLoadingText("Generating Overworld");

    double perc = 0.0;

	int lheight = groundLevel / 2;
	for (int x = 0; x < width; x++) {
        perc = (double)x / (double)width;
        SetLoadingText("Generating Overworld", perc);

		if(Math::Random(7) == 0) {
			if(Math::Random(2) == 1) {
				lheight += 1 + Math::Random(2);
			} else {
				lheight -= 1 + Math::Random(2);
			}
		}

		lheight = Math::Clamp(lheight, groundLevel / 4, groundLevel);

		// Place terrain
		for(int y = 0; y < height; y++) {
			if(y < height - lheight && y > groundLevel - 1) {
				GetTile(x, y)->type = ETileType::DIRT;
			}
		}

		// Place grass
		GetTile(x, height - lheight)->type = ETileType::GRASS;

		for(int y = 0; y < height; y++) {
			int h = lheight + Math::Random(30) + 10;
			int l = Math::Random(5) - h;

			if(y < lheight && y < l) {
				for(int y1 = 0; y1 < lheight; y1++) {
					if(y1 > h && y1 < l) {
						//tileData[x][y1]->type = 10;
					}
				}
			}
		}
	}

	isLoaded = true;
}

bool CLevel::IsLoaded() const
{
	return isLoaded;
}

void CLevel::Draw()
{
	CRect viewRect = game_local.GetViewRect();
	int viewX = (int)viewRect.pos.x;
	int viewY = (int)viewRect.pos.y;

	for(int x = viewX / TILE_SIZE; x < (viewX / TILE_SIZE) + (viewRect.width / TILE_SIZE) + 2; x++) {
		for(int y = viewY / TILE_SIZE; y < (viewY / TILE_SIZE) + (viewRect.height / TILE_SIZE) + 1; y++) {
			if(x < 0 || x >= width || y < 0 || y >= height) {
				continue;
			}
			
            CTile *tile = GetTile(x, y);
			if(tile != nullptr && tile->type != ETileType::AIR) {
				graphics->DrawTilesheet(tilesheetTex, tile->GetPosition() - viewRect.pos, (int)tile->type, 16, 16, 64, 64, 64.0f, 64.0f);
			}
		}
	}
}

bool CLevel::PlaceGrass(int x, int y)
{
    CTile *t1 = GetTile(x, y);
    CTile *t2 = GetTile(x, y - 1);
    if(y == height) {
        GetTile(x, y)->type = ETileType::GRASS;
        return false;
    } else if(GetTile(x, y - 1)->type == ETileType::AIR) {
        GetTile(x, y)->type = ETileType::GRASS;
        return true;
    } else {
        GetTile(x, y)->type = ETileType::DIRT;
        return false;
    }
}

void CLevel::AllocTileData()
{
	SetLoadingText("Allocating tile data");

    tileMemPool = new CTile[width * height]();

    double perc = 0.0;

    for(int i = 0; i < width; i++) {
        perc = (double)i / (double)width;
        SetLoadingText("Allocating tile data", perc);
        for(int j = 0; j < height; j++) {
            (&tileMemPool[width * j + i])->x = i * TILE_SIZE;
            (&tileMemPool[width * j + i])->y = j * TILE_SIZE;
            (&tileMemPool[width * j + i])->type = ETileType::AIR;
        }
    }
	common->Printf("Done!\n");
}

void CLevel::DisposeTileData()
{
    if(!tileMemPool) {
		return;
	}

    // ??? causes assert fail in VCRT on standalone build
    delete tileMemPool;

    tileMemPool = nullptr;
	isLoaded = false;
}

void CLevel::SetLoadingText(const char *text, double perc)
{
	CGUI_Loading *guiLoading = reinterpret_cast<CGUI_Loading *>(guiManager.Current());
    if(guiLoading) {
        guiLoading->SetStatusText(text, perc);
    }
}

bool CLevel::IsCollidingWithTiles(const CRect &rect)
{
	if(!isLoaded) {
		return false;
	}

	for (int x = (int)rect.pos.x / TILE_SIZE; x < ((int)rect.pos.x / TILE_SIZE) + (rect.width / TILE_SIZE) + 2; x++) {
		for (int y = (int)rect.pos.y / TILE_SIZE; y < ((int)rect.pos.y / TILE_SIZE) + (rect.height / TILE_SIZE) + 1; y++) {
			if(x < 0 || x >= width || y < 0 || y >= height) {
				continue;
			}

			CTile *tile = GetTile(x, y);

			if(tile->type == ETileType::AIR) {
				continue;
			}

			if(CRect(tile->GetPosition(), TILE_SIZE, TILE_SIZE).Collides(rect)) {
				return true;
			}
		}
	}

	return false;
}