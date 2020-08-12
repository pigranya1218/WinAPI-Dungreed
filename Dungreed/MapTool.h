#pragma once
#include "GameNode.h"
#include <commdlg.h>
#include "LinearFunc.h"

#define TILESIZE 64
#define TILEX 40
#define TILEY 30
#define SAMPLETILEX 10
#define SAMPLETILEY 20

enum class DRAW_LINE_POSITION
{
	NOLINE,
	LEFT,
	TOP,
	RIGHT,
	BOTTOM,
	LEFT_DIAGONAL, // /이런 모양
	RIGHT_DIAGONAL, // \이런 모양
	LEFT_TOP,
	RIGHT_TOP,
	LEFT_BOTTOM,
	RIGHT_BOTTOM
	
};


struct tagTileMap
{
	
	FloatRect rc;
	int tileFrameX;
	int tileFrameY;
	DRAW_LINE_POSITION linePos;
};

struct  tagPalette
{
	
	FloatRect rc;
	int tileFrameX;
	int tileFrameY;
	
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
	Vector2 _mapPointer;
	FloatRect _mapPtnRc;

	LinearFunc _line;

	FloatRect _save;
	FloatRect _load;
	FloatRect _erase;
	FloatRect _paletteLoad;

	Image* _paletteImage;
	tagTileMap _tile[TILEX * TILEY];
	tagPalette _sampleTile[SAMPLETILEX * SAMPLETILEY];

	DRAW_LINE_POSITION _drawLinePos;

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
	void paletteChange();
	void mapLoad();
	void setSelectTile();
	void releaseSelectTile();

	void setLinePos(int frameX,int frameY) ;

	Image* getImage() {	return _paletteImage;}
	tagTileMap getTile() { return _tile[TILEX * TILEY]; }
};

