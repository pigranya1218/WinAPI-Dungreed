#pragma once
#include "GameNode.h"
#include "stdafx.h"


#define TILESIZE 13

#define TILEX 20
#define TILEY 20
#define SAMPLETILEX 10
#define SAMPLETILEY 10

struct tagTile
{
	RECT rc;

	int tileFrameX;
	int tileFrameY;

};

struct  tagPalette
{
	RECT rc;
	int paletteFrameX;
	int paletteFrameY;

};

struct tagCurrentTile
{
	int x;
	int y;
};


class tileMapNode : public GameNode
{
private:

	tagTile _tile[TILEX * TILEY];
	tagPalette _sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagCurrentTile _currentTile;


public:
	HRESULT init();
	void release();
	void update();
	void render();


	void setup();
	void setMap();
	void save();
	void load();

};

