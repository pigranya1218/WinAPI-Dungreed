#include "Room6TB.h"

void Room6TB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage6_TB.map");
	

	_respawnPosition[1] = Vector2(430, 200);
	_respawnPosition[3] = Vector2(430, 800);

	/*makeDoor(Vector2(340, 70), DIRECTION::UP);
	makeDoor(Vector2(340, 920), DIRECTION::DOWN);*/
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
