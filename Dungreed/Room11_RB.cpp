#include "Room11_RB.h"

void Room11_RB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage11_RB.map");
}

void Room11_RB::release()
{
	Stage::release();
}

void Room11_RB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room11_RB::render()
{
	Stage::render();
}
