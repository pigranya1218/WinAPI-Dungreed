#include "StartRoom3.h"

void StartRoom3::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/StartRoom2_B.map");
}

void StartRoom3::release()
{
	Stage::release();
}

void StartRoom3::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void StartRoom3::render()
{
	Stage::render();
}
