#pragma once
#include "Stage.h"
#include "MapTool.h"

class TestStage : public Stage
{
private:
	Image* _tileImage;
	tagTileMap _tile[TILEX*TILEY];
	Camera _camera;

public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();

	virtual void mapLoad();
};

