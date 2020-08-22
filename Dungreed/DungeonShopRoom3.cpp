#include "DungeonShopRoom3.h"

void DungeonShopRoom3::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/DungeonShopRoom1_LR.map");

	//_respawnPosition[0] = Vector2(240, 500);
	//_respawnPosition[2] = Vector2(1600, 500);

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(600, 250), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::SHOP, Vector2(800, 650), DIRECTION::LEFT);

	_roomType = ROOMTYPE::SHOP;
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
	IMAGE_MANAGER->findImage("InDungeonShop")->setScale(4);
	CAMERA->render(IMAGE_MANAGER->findImage("InDungeonShop"), Vector2(1150, 708));
}
