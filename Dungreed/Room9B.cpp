#include "Room9B.h"
#include "StageManager.h"

void Room9B::init()
{
	Stage::init(); 
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage9_B.map");
	
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

	_respawnPosition[3] = Vector2(500, 600);
	makeDoor(Vector2(600, 900), DIRECTION::DOWN);

	_objectMgr->spawnObject(0x0000, Vector2(600, 200));
	_objectMgr->spawnObject(0x0000, Vector2(550, 200));
	_objectMgr->spawnObject(0x0002, Vector2(650, 200));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(380, 630), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room9B::release()
{
	Stage::release();
}

void Room9B::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room9B::render()
{
	Stage::render();
}
