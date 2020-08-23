#include "Room11_RB.h"

void Room11_RB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage11_RB.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_BIG_ICE, Vector2(500, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(600, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(400, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(800, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(700, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(450, 600) });
	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(600, 400);

	//_respawnPosition[2] = Vector2(1000, 600);
	_respawnPosition[3] = Vector2(450, 800);

	_objectMgr->spawnObject(0x0000, Vector2(600, 420));
	_objectMgr->spawnObject(0x0000, Vector2(550, 420));
	_objectMgr->spawnObject(0x0002, Vector2(650, 420));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(820, 420), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room11_RB::release()
{
	Stage::release();
}

void Room11_RB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room11_RB::render()
{
	Stage::render();
}
