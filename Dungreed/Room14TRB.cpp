#include "Room14TRB.h"

void Room14TRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage14_TRB.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_BOMB, Vector2(600, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_BOMB, Vector2(800, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_GIANT_NORMAL, Vector2(350, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_GIANT_RED, Vector2(1500, 300) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_MAGICIAN_ICE, Vector2(1170, 380) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(670, 550) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(940, 550) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(670, 750) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(940, 750) });
	_spawnEnemies.push_back({ ENEMY_TYPE::OVIBOS, Vector2(1000, 1000) });

	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(1000, 1000);

	_respawnPosition[3] = Vector2(1500, 930);

	_objectMgr->spawnObject(0x0000, Vector2(300, 1020));
	_objectMgr->spawnObject(0x0001, Vector2(350, 1020));
	_objectMgr->spawnObject(0x0002, Vector2(450, 1020));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(1300, 1000), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room14TRB::release()
{
	Stage::release();
}

void Room14TRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room14TRB::render()
{
	Stage::render();
}
