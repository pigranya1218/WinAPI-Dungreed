#include "Room20LTRB.h"

void Room20LTRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage20LTRB.map");
}

void Room20LTRB::release()
{
	Stage::release();
}

void Room20LTRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room20LTRB::render()
{
	Stage::render();
}
