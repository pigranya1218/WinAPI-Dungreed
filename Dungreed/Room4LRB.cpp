#include "Room4LRB.h"

void Room4LRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_LRB.map");
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
