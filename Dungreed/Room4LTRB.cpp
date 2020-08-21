#include "Room4LTRB.h"

void Room4LTRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_LTRB.map");
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
