#pragma once
#include "GameNode.h"
#include "MapTool.h"

class SampleStage : public GameNode
{
private:
	Image* _mapImage;
	tagTileMap _tile[TILEX*TILEY];
	Camera _camera;

public:
	HRESULT init();
	void release();
	void update();
	void render();
	void mapLoad();
};

