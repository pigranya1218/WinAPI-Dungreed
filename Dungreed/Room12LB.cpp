#include "Room12LB.h"

void Room12LB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage12_LB.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_MAGICIAN_ICE, Vector2(1040, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(600, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_BIG_ICE, Vector2(400, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(500, 800) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(300, 800) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(1000, 800) });

	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(700, 600);

	_respawnPosition[3] = Vector2(650, 980);

	_objectMgr->spawnObject(0x0000, Vector2(800, 605));
	_objectMgr->spawnObject(0x0001, Vector2(750, 605));
	_objectMgr->spawnObject(0x0002, Vector2(900, 605));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(550, 600), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room12LB::release()
{
	Stage::release();
}

void Room12LB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room12LB::render()
{
	Stage::render();
}
