#include "Room6TB.h"

void Room6TB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage6_TB.map");
	

	_respawnPosition[1] = Vector2(600, 200);
	_respawnPosition[3] = Vector2(600, 800);
}

void Room6TB::release()
{
	Stage::release();
}

void Room6TB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room6TB::render()
{
	Stage::render();
}
