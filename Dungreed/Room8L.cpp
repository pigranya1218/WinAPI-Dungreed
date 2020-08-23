#include "Room8L.h"
#include "StageManager.h"

void Room8L::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage8_L.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(700, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(800, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(750, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(650, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(500, 900) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(900, 900) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(1000, 850) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(380, 800) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_GIANT_NORMAL, Vector2(1100, 500) });
	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(750, 900);

	_objectMgr->spawnObject(0x0000, Vector2(1100, 920));
	_objectMgr->spawnObject(0x0000, Vector2(1040, 920));
	_objectMgr->spawnObject(0x0001, Vector2(1180, 920));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(570, 900), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room8L::release()
{
	Stage::release();
}

void Room8L::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room8L::render()
{
	Stage::render();
}
