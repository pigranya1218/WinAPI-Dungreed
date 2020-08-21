#include "Room1R.h"
#include "StageManager.h"

void Room1R::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage1_R.map");

	_respawnPosition[2] = Vector2(1750,500);
}

void Room1R::release()
{
	Stage::release();
}

void Room1R::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room1R::render()
{
	Stage::render();
}
