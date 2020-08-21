#include "Room13LTB.h"

void Room13LTB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage13_LTB.map");
	
}

void Room13LTB::release()
{
	Stage::release();
}

void Room13LTB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room13LTB::render()
{
	Stage::render();
}
