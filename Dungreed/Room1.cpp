#include "Room1.h"

void Room1::init()
{

    Stage:: init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage21.map");
}

void Room1::release()
{
	Stage::release();
}

void Room1::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room1::render()
{
	Stage::render();
}
