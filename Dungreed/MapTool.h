#pragma once
#include "GameNode.h"
#include <commdlg.h>
#include "LinearFunc.h"

#define TILESIZE 32
#define TILEX 30
#define TILEY 20
#define SAMPLETILEX 10
#define SAMPLETILEY 20

struct tagTileMap
{
	FloatRect rc;
	int tileFrameX;
	int tileFrameY;
	int linePos[2][2];
};

struct  tagPalette
{
	FloatRect rc;
	int tileFrameX;
	int tileFrameY;
	int linePos[2][2];
};

struct tagSelectTile
{
	FloatRect rc;
	int x;
	int y;
};


class MapTool : public GameNode
{
private:

	enum class TOOLMENU
	{
			SAVE,
			LOAD,
			SELECTTILE,
			ERASE,
	};

	//HWND _saveBtn;
	//HWND _loadBtn;
	
	LinearFunc _line;
	Camera _camera;

	FloatRect _save;
	FloatRect _load;
	FloatRect _erase;

	Image* _paletteImage;
	tagTileMap _tile[TILEX * TILEY];
	tagPalette _sampleTile[SAMPLETILEX * SAMPLETILEY];

	vector<tagSelectTile> _vSelectTile;
	vector<tagSelectTile>::iterator _viSelectTile;

	vector<tagTileMap> _vTileMap;
	vector<tagTileMap>::iterator _viTileMap;

	vector<TCHAR*> _vLoad;
	vector<TCHAR*>::iterator _viLoad;

public:
	HRESULT init();
	
	void release();
	void update();
	void render();
	

	void setup();
	void setMap();
	void save();
	void load();
	void mapLoad();
	void setSelectTile();
	void releaseSelectTile();

	Image* getImage() {	return _paletteImage;}
	tagTileMap getTile() { return _tile[TILEX * TILEY]; }
};

