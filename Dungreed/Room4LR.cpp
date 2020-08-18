#include "Room4LR.h"

void Room4LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage4LR.map");
}

void Room4LR::release()
{
	Stage::release();
}

void Room4LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);

}

void Room4LR::render()
{
	Stage::render();
}
