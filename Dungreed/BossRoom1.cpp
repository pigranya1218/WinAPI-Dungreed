#include "BossRoom1.h"

void BossRoom1::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/BossRoom.map");


}

void BossRoom1::release()
{
	Stage::release();
}

void BossRoom1::update(float const elapsedTime)
{
	Stage::update(elapsedTime);


}

void BossRoom1::render()
{
	Stage::render();


}
