#include "Room14TRB.h"

void Room14TRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage14_TRB.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600) });
	_spawnChest.spawn = true;
	_spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(500, 500);

	_respawnPosition[3] = Vector2(1500, 930);

	_objectMgr->spawnObject(0x0000, Vector2(300, 500));
	_objectMgr->spawnObject(0x0001, Vector2(350, 500));
	_objectMgr->spawnObject(0x0002, Vector2(450, 500));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(1300, 1000), DIRECTION::LEFT);
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
