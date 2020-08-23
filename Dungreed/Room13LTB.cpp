#include "Room13LTB.h"

void Room13LTB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage13_LTB.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::BANSHEE, Vector2(700, 350) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_MAGICIAN_ICE, Vector2(1240, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_ICE, Vector2(600, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_ICE, Vector2(650, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(540, 650) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(490, 800) });
	_spawnEnemies.push_back({ ENEMY_TYPE::MINOTAURS, Vector2(550, 800) });

	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(450, 500);

	_respawnPosition[3] = Vector2(300, 800);

	makeDoor(Vector2(309, 1100), DIRECTION::DOWN);

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(1000, 400), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room13LTB::release()
{
	Stage::release();
}

void Room13LTB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room13LTB::render()
{
	Stage::render();
}
