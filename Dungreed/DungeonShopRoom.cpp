#include "DungeonShopRoom.h"

void DungeonShopRoom::init()
{
	Stage::init();

	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("DungeonShopRoom1.map");
}

void DungeonShopRoom::release()
{
	Stage::release();
}

void DungeonShopRoom::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void DungeonShopRoom::render()
{
	Stage::render();

	IMAGE_MANAGER->findImage("InDungeonShop")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("InDungeonShop"), Vector2(600, 700));
}
