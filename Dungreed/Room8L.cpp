#include "Room8L.h"

void Room8L::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage8L.map");
}

void Room8L::release()
{
	Stage::release();
}

void Room8L::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room8L::render()
{
	Stage::render();
}
