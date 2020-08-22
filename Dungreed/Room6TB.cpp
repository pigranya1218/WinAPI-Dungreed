#include "Room6TB.h"

void Room6TB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage6_TB.map");
	
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

	//_respawnPosition[1] = Vector2(560, 200);
      _respawnPosition[3] = Vector2(500, 800);

	/*makeDoor(Vector2(340, 70), DIRECTION::UP);
	makeDoor(Vector2(340, 920), DIRECTION::DOWN);*/

	//_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(600, 600), DIRECTION::LEFT);

	  _roomType = ROOMTYPE::NORMAL;
}

void Room6TB::release()
{
	Stage::release();
}

void Room6TB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room6TB::render()
{
	Stage::render();
}
