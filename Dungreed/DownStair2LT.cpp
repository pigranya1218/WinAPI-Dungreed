#include "DownStair2LT.h"

void DownStair2LT::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/DownStair2_LT.map");

	_respawnPosition[0] = Vector2(120, 480);
	_respawnPosition[1] = Vector2(650, 300);
}

void DownStair2LT::release()
{
	Stage::release();
}

void DownStair2LT::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void DownStair2LT::render()
{
	Stage::render();
}
