#include "DownStair1L.h"

void DownStair1L::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/DownStair1_L.map");
}

void DownStair1L::release()
{
	Stage::release();
}

void DownStair1L::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void DownStair1L::render()
{
	Stage::render();
}
