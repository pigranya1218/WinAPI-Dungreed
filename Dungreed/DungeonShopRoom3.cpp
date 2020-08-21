#include "DungeonShopRoom3.h"

void DungeonShopRoom3::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/DungeonShopRoom1_LR.map");

	_respawnPosition[0] = Vector2(240, 500);
	_respawnPosition[2] = Vector2(1700, 500);
}

void DungeonShopRoom3::release()
{
	Stage::release();
}

void DungeonShopRoom3::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void DungeonShopRoom3::render()
{
	Stage::render();
}
