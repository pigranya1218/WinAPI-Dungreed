#include "Room3LR.h"

void Room3LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage3LR.map");
}

void Room3LR::release()
{
	Stage::release();
}

void Room3LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room3LR::render()
{
	Stage::render();
}
