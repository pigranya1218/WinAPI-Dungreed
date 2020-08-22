#include "Room23LR.h"

void Room23LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage23_LR.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600) });
	_spawnChest.spawn = true;
	_spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(500, 500);
	
	_objectMgr->spawnObject(0x0001, Vector2(700, 500));
	_objectMgr->spawnObject(0x0001, Vector2(740, 500));
	_objectMgr->spawnObject(0x0002, Vector2(780, 500));

	_objectMgr->spawnObject(0x0000, Vector2(1100, 500));
	_objectMgr->spawnObject(0x0000, Vector2(1140, 500));
	_objectMgr->spawnObject(0x0001, Vector2(1180, 500));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(600, 600), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room23LR::release()
{
	Stage::release();
}

void Room23LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room23LR::render()
{
	Stage::render();
}
