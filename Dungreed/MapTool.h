#pragma once
#include "GameNode.h"
#include <commdlg.h>
#include "LinearFunc.h"

#define TILESIZE 64

#define SAMPLETILEX 10
#define SAMPLETILEY 10

enum class DRAW_LINE_POSITION
{
	NOLINE,
	LEFT,
	TOP,
	RIGHT,
	BOTTOM,
	LEFT_DIAGONAL, // /�̷� ���
	RIGHT_DIAGONAL, // \�̷� ���
	
	//�κ� �̻� �׷��� ���
	LEFT_TOP,
	RIGHT_TOP,
	LEFT_BOTTOM,
	RIGHT_BOTTOM,
	
	//�����������ΰ�?
	PLATFORM
};


struct tagTileMap
{
	
	FloatRect rc;
	int tileFrameX;
	int tileFrameY;
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

struct tagSelectTile
{
	FloatRect rc;
	int x;
	int y;
	
};

struct tagMap
{
	int Tx;
	int Ty;
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

	
	
	Synthesize(int, _tileX, TileX)
	Synthesize(int, _tileY, TileY)

	

	Vector2 _mapPointer;
	FloatRect _mapPtnRc;

	LinearFunc _line;

	FloatRect _save;
	FloatRect _load;
	FloatRect _erase;
	FloatRect _paletteLoad;
	FloatRect _increaseTileX, _decreaseTileX;
	FloatRect _increaseTileY, _decreaseTileY;


	Image* _paletteImage;
	tagTileMap _tile[2000];
	tagPalette _sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagMap _map[1];

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

	void setTileSize();

	


};

