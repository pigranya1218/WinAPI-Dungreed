#include "Room2.h"

void Room2::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage20.map");
}

void Room2::release()
{
	Stage::release();
}

void Room2::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room2::render()
{
	Stage::render();
}
