#include "Room5LR.h"
#include "StageManager.h"

void Room5LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage5LR.map");
	_OpenDirection[0] = true;
	_OpenDirection[1] = false;
	_OpenDirection[2] = true;
	_OpenDirection[3] = false;
	
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
