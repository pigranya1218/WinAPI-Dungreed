#include "Room8L.h"
#include "StageManager.h"

void Room8L::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage8_L.map");
	//_respawnPosition[0] = Vector2(160, 680);

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400), 1 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500), 1 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600), 1 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400), 2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500), 2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600), 2 }); 
	_spawnChest.spawn = true;
	_spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(500, 500);

	_objectMgr->spawnObject(0x0000, Vector2(1200, 810));
	_objectMgr->spawnObject(0x0000, Vector2(1240, 810));
	_objectMgr->spawnObject(0x0001, Vector2(1280, 810));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(570, 810), DIRECTION::LEFT);

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
