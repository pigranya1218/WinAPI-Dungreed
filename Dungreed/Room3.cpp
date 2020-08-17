#include "Room3.h"

void Room3::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage22.map");
}

void Room3::release()
{
	Stage::release();

}

void Room3::update(float const elapsedTime)
{
	Stage::update(elapsedTime);

}

void Room3::render()
{
	Stage::render();
}
