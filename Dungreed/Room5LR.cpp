#include "Room5LR.h"
#include "StageManager.h"

void Room5LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage5_LR.map");
	
	
}

void Room5LR::release()
{
	Stage::release();
}

void Room5LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room5LR::render()
{
	Stage::render();
}
