#pragma once
#include "GameNode.h"



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
	HWND _saveBtn;
	HWND _loadBtn;
	

	Image* _paletteImage;
	tagTileMap _tile[TILEX * TILEY];
	tagPalette _sampleTile[SAMPLETILEX * SAMPLETILEY];

	vector<tagSelectTile> _vSelectTile;
	vector<tagSelectTile>::iterator _viSelectTile;

public:
	HRESULT init();
	
	void release();
	void update();
	void render();


	void setup();
	void setMap();
	void save();
	void load();

	void setSelectTile();
	void releaseSelectTile();

};

