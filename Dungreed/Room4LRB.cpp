#include "Room4LRB.h"

void Room4LRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_LRB.map");

	_respawnPosition[0] = Vector2(100,600);
	
	_respawnPosition[2] = Vector2(900,600);
	_respawnPosition[3] = Vector2(450, 800);
}

void Room4LRB::release()
{
	Stage::release();
}

void Room4LRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room4LRB::render()
{
	Stage::render();
}
