#include "Room20LRB.h"

void Room20LRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage20_LRB.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600) });
	_spawnChest.spawn = true;
	_spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(500, 500);
	
	_respawnPosition[3] = Vector2(400, 800);

	_objectMgr->spawnObject(0x0000, Vector2(300, 500));
	_objectMgr->spawnObject(0x0001, Vector2(350, 500));
	_objectMgr->spawnObject(0x0002, Vector2(450, 500));

	_objectMgr->spawnObject(0x0000, Vector2(220, 800));
	_objectMgr->spawnObject(0x0001, Vector2(270, 800));


	_objectMgr->spawnObject(0x0002, Vector2(800, 2500));

	_objectMgr->spawnObject(0x0000, Vector2(840, 2500));
	_objectMgr->spawnObject(0x0001, Vector2(880, 2500));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(900, 350), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room20LRB::release()
{
	Stage::release();
}

void Room20LRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	if (KEY_MANAGER->isOnceKeyDown(VK_F8))
	{

		//_stageManager->moveRoom();

	}
}

void Room20LRB::render()
{
	Stage::render();
}