#include "Room12LB.h"

void Room12LB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage12_LB.map");

	_respawnPosition[0] = Vector2(200, 600);

	
	_respawnPosition[3] = Vector2(450, 800);
}

void Room12LB::release()
{
	Stage::release();
}

void Room12LB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room12LB::render()
{
	Stage::render();
}
