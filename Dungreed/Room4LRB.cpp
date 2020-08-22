#include "Room4LRB.h"

void Room4LRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_LRB.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400), 1 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500), 1 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600), 1 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400), 2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500), 2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600), 2 }); 
	_spawnChest.spawn = true;
	_spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(500, 500);


	_respawnPosition[3] = Vector2(750, 1300);

	_objectMgr->spawnObject(0x0000, Vector2(1600, 1300));

	_objectMgr->spawnObject(0x0001, Vector2(500, 500));
	_objectMgr->spawnObject(0x0001, Vector2(600, 500));

	_objectMgr->spawnObject(0x0002, Vector2(650, 500));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(600, 600), DIRECTION::LEFT);

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
