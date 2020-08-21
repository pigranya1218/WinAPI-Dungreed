#include "Room4LTRB.h"

void Room4LTRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_LTRB.map");
	_respawnPosition[0] = Vector2(100, 600);
	_respawnPosition[1] = Vector2(300,200);
	_respawnPosition[2] = Vector2(900, 600);
	_respawnPosition[3] = Vector2(450, 800);
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
