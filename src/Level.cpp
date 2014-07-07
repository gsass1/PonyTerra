#include "ICommon.h"
#include "File.h"
#include "IFilesystem.h"
#include "Game.h"
#include "IGraphics.h"
#include "Level.h"
#include "IResourceManager.h"
#include "ITexture.h"

#include "MutexLock.h"

#include "GUIManager.h"
#include "GUI_Loading.h"

//--------------------------------------------------

std::thread *levelGenThread = NULL;

CLevelGenerate levelGenerate;

namespace
{

void StartGenerating() {
	level.Generate(level.width, level.height);

	{
		CMutexLock lock(&levelGenerate.stateLock);
		levelGenerate.isGenerating = false;
	}
}

}

//--------------------------------------------------

void CLevelGenerate::StartGenerating() {
	isGenerating = true;
	levelGenThread = new std::thread(::StartGenerating);
}

//--------------------------------------------------

CLevel level;

CLevel::CLevel() {
	width = height = 0;
	tilesheetTex = nullptr;
	tileData = nullptr;
	time = 0;
	isBossSummoned = false;

	isLoaded = false;
}

CLevel::~CLevel() {
}

void CLevel::Initialize() {
	tilesheetTex = resMgr->GetTexture("data/res/tex/tilesheet.png");
}

void CLevel::Load(const char *filepath) {
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

void CLevel::Generate(int width, int height) {
	this->width = width;
	this->height = height;

	AllocTileData();

	isLoaded = true;
}

bool CLevel::IsLoaded() const {
	return isLoaded;
}

void CLevel::Draw() {
	CRect viewRect = game_local.GetViewRect();
	int viewX = (int)viewRect.pos.x;
	int viewY = (int)viewRect.pos.y;

	for (int x = viewX / TILE_SIZE; x < (viewX / TILE_SIZE) + (viewRect.width / TILE_SIZE) + 1; x++) {
		for (int y = viewY / TILE_SIZE; y < (viewY / TILE_SIZE) + (viewRect.height / TILE_SIZE) + 1; y++) {
			CTile *tile = tileData[x][y];
			if(tile != nullptr && tile->type != ETileType::AIR) {
				graphics->DrawTilesheet(tilesheetTex, tile->GetPosition() - viewRect.pos, (int)tile->type, 16, 16, 64, 64, 64.0f, 64.0f);
			}
		}
	}
}

void CLevel::AllocTileData() {
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

void CLevel::DisposeTileData() {
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

void CLevel::SetLoadingText(const char *text) {
	CGUI_Loading *guiLoading = NULL;
	guiLoading = reinterpret_cast<CGUI_Loading *>(guiManager.Current());
	//ASSERT(guiLoading);

	guiLoading->SetStatusText(text);
}
