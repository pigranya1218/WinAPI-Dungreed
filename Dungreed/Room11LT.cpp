#include "Room11LT.h"

void Room11LT::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage11_LT.map");

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
	
	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(750, 450), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room11LT::release()
{
	Stage::release();
}

void Room11LT::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room11LT::render()
{
	Stage::render();
}
