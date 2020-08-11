#pragma once
#include "Stage.h"
#include "MapTool.h"

class TestStage : public Stage
{
private:
	Image* _tileImage;
	tagTileMap _tile[TILEX*TILEY];
	int _currentIndex;

public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();

	void mapLoad();
};

