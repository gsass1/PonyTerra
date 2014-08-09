#include "ICommon.h"
#include "File.h"
#include "IFilesystem.h"
#include "Game.h"
#include "IGraphics.h"
#include "Level.h"
#include "NoiseGenerator.h"
#include "IResourceManager.h"
#include "ITexture.h"

#include "MutexLock.h"

#include "GUIManager.h"
#include "GUI_Loading.h"

//--------------------------------------------------

std::thread *levelGenThread = NULL;

CLevelGenerate levelGenerate;

static void StartGenerating()
{
	level.Generate(level.width, level.height);

	{
		CMutexLock lock(&levelGenerate.stateLock);
		levelGenerate.isGenerating = false;
	}
}


//--------------------------------------------------

void CLevelGenerate::StartGenerating()
{
	isGenerating = true;
	levelGenThread = new std::thread(::StartGenerating);
}

//--------------------------------------------------

CLevel level;

CLevel::CLevel()
{
	width = height = 0;
	tilesheetTex = nullptr;
	tileData = nullptr;
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

void CLevel::Load(const char *filepath)
{
	if(isLoaded) {
		common->Error("%s", "Cannot load new level while a level is already loaded!\n");
	}

	IFile *file = fileSystem->OpenFile(filepath, EFileMode::READ);

	width = file->ReadInt32();
	height = file->ReadInt32();

	if(!width || !height || width < 0 || height < 0) {
		common->Error("Corrupt Level File\n");
	}

	AllocTileData();

	time = file->ReadDouble();
	isBossSummoned = file->ReadByte() == 1;

	//file->ReadVector2f(player.pos);
	file->ReadVector2f(spawnPos);

	isLoaded = true;
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
				tileData[x][y]->type = ETileType::DIRT;
			}
		}
	}

	SetLoadingText("Generating Overworld");

	int lheight = groundLevel / 2;
	for (int x = 0; x < width; x++) {
		if(Math::Random(7) == 0) {
			if(Math::Random(2) == 1) {
				lheight += 1 + Math::Random(2);
			} else {
				lheight -= 1 + Math::Random(2);
			}
		}

		lheight = Math::Clamp(lheight, groundLevel / 4, groundLevel);

		for(int y = 0; y < height; y++) {
			if(y < height - lheight && y > groundLevel - 1) {
                PlaceGrass(x, y);
				//tileData[x][y]->type = ETileType::DIRT;
			}
		}

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

	for(int x = viewX / TILE_SIZE; x < (viewX / TILE_SIZE) + (viewRect.width / TILE_SIZE) + 1; x++) {
		for(int y = viewY / TILE_SIZE; y < (viewY / TILE_SIZE) + (viewRect.height / TILE_SIZE) + 1; y++) {
			if(x < 0 || x >= width || y < 0 || y >= height) {
				continue;
			}
			
			CTile *tile = tileData[x][y];
			if(tile != nullptr && tile->type != ETileType::AIR) {
				graphics->DrawTilesheet(tilesheetTex, tile->GetPosition() - viewRect.pos, (int)tile->type, 16, 16, 64, 64, 64.0f, 64.0f);
			}
		}
	}
}

bool CLevel::PlaceGrass(int x, int y)
{
    if(y == height) {
        tileData[x][y]->type = ETileType::GRASS;
        return false;
    } else if(tileData[x][y - 1]->type == ETileType::AIR) {
        tileData[x][y]->type = ETileType::GRASS;
        return true;
    } else {
        tileData[x][y]->type = ETileType::DIRT;
        return false;
    }
}

void CLevel::AllocTileData()
{
	SetLoadingText("Allocating tile data");

	tileData = new CTile**[width];
	for(int i = 0; i < width; i++) {
		tileData[i] = new CTile*[height];
	}

	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			tileData[i][j] = new CTile(i * TILE_SIZE, j * TILE_SIZE, ETileType::AIR);
		}
	}

	common->Printf("Done!\n");
}

void CLevel::DisposeTileData()
{
	if(!tileData) {
		return;
	}

	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			delete tileData[i][j];
		}
		delete tileData[height];
	}
	delete tileData[width];

	tileData = nullptr;
	isLoaded = false;
}

void CLevel::SetLoadingText(const char *text)
{
	CGUI_Loading *guiLoading = reinterpret_cast<CGUI_Loading *>(guiManager.Current());
    if(guiLoading) {
        guiLoading->SetStatusText(text);
    }
}

bool CLevel::IsCollidingWithTiles(const CRect &rect)
{
	if(!isLoaded) {
		return false;
	}

	for (int x = (int)rect.pos.x / TILE_SIZE; x < ((int)rect.pos.x / TILE_SIZE) + (rect.width / TILE_SIZE) + 1; x++) {
		for (int y = (int)rect.pos.y / TILE_SIZE; y < ((int)rect.pos.y / TILE_SIZE) + (rect.height / TILE_SIZE) + 1; y++) {
			if(x < 0 || x >= width || y < 0 || y >= height) {
				continue;
			}

			CTile *tile = tileData[x][y];

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