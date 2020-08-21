#include "DungeonShopRoom3.h"

void DungeonShopRoom3::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/DungeonShopRoom1_LR.map");

	_objectMgr->spawnObject(0x0001, Vector2(520, 200));	

	_objectMgr->spawnObject(0x0002, Vector2(600, 200));
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
