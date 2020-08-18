#include "Room2LTR.h"

void Room2LTR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage2LTR.map");
}

void Room2LTR::release()
{
	Stage::release();
}

void Room2LTR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room2LTR::render()
{
	Stage::render();
}
