#include "Room7RT.h"

void Room7RT::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage7_TR.map");
}

void Room7RT::release()
{
Stage:: release();
}

void Room7RT::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room7RT::render()
{
	Stage::render();
}
