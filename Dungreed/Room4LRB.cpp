#include "Room4LRB.h"

void Room4LRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(300, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(300, 650) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(300, 860) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(1620, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(1620, 650) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(1620, 860) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_GIANT_NORMAL, Vector2(970, 350) });
	_spawnEnemies.push_back({ ENEMY_TYPE::MINOTAURS, Vector2(990, 650) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BANSHEE, Vector2(960, 980) });

	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(1000, 620);

	_objectMgr->spawnObject(0x0000, Vector2(1600, 1300));

	_objectMgr->spawnObject(0x0001, Vector2(500, 500));
	_objectMgr->spawnObject(0x0001, Vector2(600, 500));

	_objectMgr->spawnObject(0x0002, Vector2(650, 500));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(1000, 1320), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room4LRB::release()
{
	Stage::release();
}

void Room4LRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room4LRB::render()
{
	Stage::render();
}
