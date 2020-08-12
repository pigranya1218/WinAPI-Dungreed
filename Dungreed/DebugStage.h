#pragma once
#include "Stage.h"
#include "MapTool.h"

class DebugStage : public Stage
{
private:
	Image* _tileImage;
	tagTileMap _tile[2000];
	tagMap _map[1];
	int _currentIndex;

public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();

	void mapLoad();
};
