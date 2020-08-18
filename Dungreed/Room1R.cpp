#include "Room1R.h"

void Room1R::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage1R.map");
}

void Room1R::release()
{
	Stage::release();
}

void Room1R::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room1R::render()
{
	Stage::render();
}
