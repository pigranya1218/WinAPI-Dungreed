#pragma once
#include "Stage.h"
#include "MapTool.h"

class TestStage : public Stage
{
private:

	tagTileMap _tile;

public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();

	virtual void mapLoad();
};

