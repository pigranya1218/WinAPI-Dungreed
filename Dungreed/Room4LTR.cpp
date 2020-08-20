#include "Room4LTR.h"

void Room4LTR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_LTR.map");
}

void Room4LTR::release()
{
	Stage::release();
}

void Room4LTR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room4LTR::render()
{
	Stage::render();
}
