#include "Room12LRB.h"

void Room12LRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage12_LRB.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600) });
	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(500, 500);

	_respawnPosition[3] = Vector2(600, 820);

	_objectMgr->spawnObject(0x0000, Vector2(600, 320));
	_objectMgr->spawnObject(0x0001, Vector2(550, 320));
	_objectMgr->spawnObject(0x0002, Vector2(650, 320));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(600, 600), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room12LRB::release()
{
	Stage::release();
}

void Room12LRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room12LRB::render()
{
	Stage::render();
}
