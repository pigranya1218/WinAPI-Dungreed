#include "StartRoom2.h"

void StartRoom2::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("StartRoom2.map");

	_OpenDirection[0] = false;
	_OpenDirection[1] = false;
	_OpenDirection[2] = true;
	_OpenDirection[3] = true;
}

void StartRoom2::release()
{
	Stage::release();
}

void StartRoom2::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void StartRoom2::render()
{
	Stage::render();
}
