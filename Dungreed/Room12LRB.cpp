#include "Room12LRB.h"

void Room12LRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage12_LRB.map");

	_respawnPosition[0] = Vector2(200, 600);

	_respawnPosition[2] = Vector2(900, 600);
	_respawnPosition[3] = Vector2(600, 820);
}

void Room12LRB::release()
{
	Stage::release();
}

void Room12LRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room12LRB::render()
{
	Stage::render();
}
