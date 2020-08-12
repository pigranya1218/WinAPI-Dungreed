#pragma once
#include "GameNode.h"
#include "MapTool.h"

class SampleStage : public GameNode
{
private:
	Image* _mapImage;
	MapTool _map;
	tagTileMap _tile[1000];
	
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void mapLoad();
};

