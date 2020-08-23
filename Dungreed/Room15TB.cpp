#include "Room15TB.h"

void Room15TB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage15_TB.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::MINOTAURS, Vector2(800, 1000) });
	_spawnEnemies.push_back({ ENEMY_TYPE::OVIBOS, Vector2(600, 300) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_NORMAL, Vector2(900, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_NORMAL, Vector2(800, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_RED, Vector2(200, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_RED, Vector2(800, 500) });

	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(800, 300);

	_respawnPosition[3] = Vector2(490, 1120);

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(800, 1000), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room15TB::release()
{
	Stage::release();
}

void Room15TB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room15TB::render()
{
	Stage::render();
}
