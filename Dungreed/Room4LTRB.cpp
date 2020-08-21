#include "Room4LTRB.h"

void Room4LTRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_LTRB.map");
	_respawnPosition[0] = Vector2(150, 1300);
	_respawnPosition[1] = Vector2(750,200);
	_respawnPosition[2] = Vector2(1600, 1300);
	_respawnPosition[3] = Vector2(750, 1300);
}

void Room4LTRB::release()
{
	Stage::release();
}

void Room4LTRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room4LTRB::render()
{
	Stage::render();
}
