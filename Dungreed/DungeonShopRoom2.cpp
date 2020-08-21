#include "DungeonShopRoom2.h"

void DungeonShopRoom2::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/DungeonShopRoom1_R.map");

	_objectMgr->spawnObject(0x0001, Vector2(520, 200));	

	_objectMgr->spawnObject(0x0002, Vector2(600, 200));
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
