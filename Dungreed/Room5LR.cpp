#include "Room5LR.h"
#include "StageManager.h"

void Room5LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage5_LR.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::BANSHEE, Vector2(1000, 1220) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(600, 1280) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(1310, 1280) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(710, 1600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(800, 1600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(1200, 1600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(1100, 1600) });

	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(970, 500);

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(1200, 1600), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room5LR::release()
{
	Stage::release();
}

void Room5LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room5LR::render()
{
	Stage::render();
}
