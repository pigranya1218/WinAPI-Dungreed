#include "DungeonShopRoom2.h"

void DungeonShopRoom2::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/DungeonShopRoom1_R.map");

	//_respawnPosition[2] = Vector2(1600, 500);
}

void DungeonShopRoom2::release()
{
	Stage::release();
}

void DungeonShopRoom2::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void DungeonShopRoom2::render()
{
	Stage::render();
}
