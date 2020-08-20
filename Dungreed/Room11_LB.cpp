#include "Room11_LB.h"

void Room11_LB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage11_LB.map");
}

void Room11_LB::release()
{
	Stage::release();
}

void Room11_LB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room11_LB::render()
{
	Stage::render();
}
