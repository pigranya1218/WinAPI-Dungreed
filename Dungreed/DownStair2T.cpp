#include "DownStair2T.h"

void DownStair2T::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/DownStair2_T.map");
}

void DownStair2T::release()
{
	Stage::release();
}

void DownStair2T::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void DownStair2T::render()
{
	Stage::render();
}
