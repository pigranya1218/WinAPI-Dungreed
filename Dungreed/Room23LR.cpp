#include "Room23LR.h"

void Room23LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage23_LR.map");

	_respawnPosition[0] = Vector2(200, 200);
	
	_respawnPosition[2] = Vector2(600, 200);
	
}

void Room23LR::release()
{
	Stage::release();
}

void Room23LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room23LR::render()
{
	Stage::render();
}
