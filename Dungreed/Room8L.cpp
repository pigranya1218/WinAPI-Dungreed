#include "Room8L.h"
#include "StageManager.h"

void Room8L::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage8_L.map");
}

void Room8L::release()
{
	Stage::release();
}

void Room8L::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room8L::render()
{
	Stage::render();
}
