#include "Room7_RB.h"

void Room7_RB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage7_RB.map");
}

void Room7_RB::release()
{
	Stage::release();
}

void Room7_RB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room7_RB::render()
{
	Stage::render();
}
