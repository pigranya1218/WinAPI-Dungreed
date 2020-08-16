#pragma once
#include <commdlg.h>
#include "LinearFunc.h"

#define TILESIZE 64
#define MAXTILEX 150
#define MAXTILEY 150
#define SAMPLETILEX 10
#define SAMPLETILEY 10

enum class DRAW_LINE_POSITION
{
	NOLINE,
	LEFT,
	TOP,
	RIGHT,
	BOTTOM,
	LEFT_DIAGONAL, // /이런 모양
	RIGHT_DIAGONAL, // \이런 모양
	
	//두변 이상 그려질 경우
	LEFT_TOP,
	RIGHT_TOP,
	LEFT_BOTTOM,
	RIGHT_BOTTOM,
	
	//프랫폼형태인가?
	PLATFORM
};

//struct tagTileMap
//{
//	int maxTileX;
//	int maxTileY;
//	tagTile 
//};

struct tagTileMap
{
	
	FloatRect rc;
	int tileFrameX[2];
	int tileFrameY[2];
	DRAW_LINE_POSITION linePos;
	int tileX;
	int tileY;
	
};

struct  tagPalette
{
	
	FloatRect rc;
	int tileFrameX;
	int tileFrameY;
	
};

struct tagMap
{
	int Tx;
	int Ty;
};


class MapTool
{
private:

	enum class TOOLMENU
	{
		SAVE,
		LOAD,
		SELECTTILE,
		ERASE,
	};
	
	Synthesize(int, _tileX, TileX)
	Synthesize(int, _tileY, TileY)

	int _layer;

	FloatRect _mapPtnRc;

	LinearFunc _line;

	FloatRect _save;
	FloatRect _load;
	FloatRect _erase;
	FloatRect _layer1Btn, _layer2Btn;
	FloatRect _increaseTileX, _decreaseTileX;
	FloatRect _increaseTileY, _decreaseTileY;
	
	int _paletteNum;
	Image* _paletteImage;
	
	tagTileMap _tile[MAXTILEX*MAXTILEY];
	tagPalette _sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagPalette _aniPalette[4];

	bool _selectDrag;
	Vector2 _selectStart;
	Vector2 _selectEnd;

	DRAW_LINE_POSITION _drawLinePos;

	vector<TCHAR*> _vLoad;

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

	void setLinePos(int frameX,int frameY) ;

	void setTileSize();

};

