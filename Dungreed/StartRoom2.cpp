#include "StartRoom2.h"

void StartRoom2::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("StartRoom2.map");
	_direction.push_back(DIRECTION::RIGHT);
	_direction.push_back(DIRECTION::DOWN);
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
