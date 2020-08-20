#include "Room9B.h"
#include "StageManager.h"

void Room9B::init()
{
	Stage::init(); 
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage9_B.map");

}

void Room9B::release()
{
	Stage::release();
}

void Room9B::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room9B::render()
{
	Stage::render();
}
