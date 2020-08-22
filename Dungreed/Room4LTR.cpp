#include "Room4LTR.h"

void Room4LTR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_LTR.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400), 1 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500), 1 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600), 1 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400), 2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500), 2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600), 2 });
	_spawnChest.spawn = true;
	_spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(500, 500);

	_objectMgr->spawnObject(0x0000, Vector2(1600, 1300));

	_objectMgr->spawnObject(0x0001, Vector2(500, 500));
	_objectMgr->spawnObject(0x0001, Vector2(900, 1000));

	_objectMgr->spawnObject(0x0002, Vector2(650, 1000));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(600, 720), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room4LTR::release()
{
	Stage::release();
}

void Room4LTR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room4LTR::render()
{
	Stage::render();
}
