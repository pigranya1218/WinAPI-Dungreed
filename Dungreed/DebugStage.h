#pragma once
#include "Stage.h"
#include "MapTool.h"

class DebugStage : public Stage
{
private:
	
	tagTileMap _tile[2000],_tile2[2000];
	MapTool* _map;
	int _currentIndex;

public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();

	//void mapLoad();
};
