#include "Room9B.h"
#include "StageManager.h"

void Room9B::init()
{
	Stage::init(); 
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage9_B.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(850, 450) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(350, 450) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_RED, Vector2(900, 370) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_RED, Vector2(300, 370) });

	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(600, 750);

	_respawnPosition[3] = Vector2(500, 600);
	makeDoor(Vector2(600, 900), DIRECTION::DOWN);

	_objectMgr->spawnObject(0x0000, Vector2(600, 250));
	_objectMgr->spawnObject(0x0000, Vector2(550, 250));
	_objectMgr->spawnObject(0x0002, Vector2(650, 250));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(400, 750), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room9B::release()
{
	Stage::release();
}

void Room9B::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room9B::render()
{
	Stage::render();
}
