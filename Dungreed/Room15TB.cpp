#include "Room15TB.h"

void Room15TB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage15_TB.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600) });
	_spawnChest.spawn = true;
	_spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(500, 500);

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
