#include "Room21LR.h"
#include "StageManager.h"

void Room21LR::init()
{

    Stage:: init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage21_LR.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400), 1 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500), 1 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600), 1 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400), 2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500), 2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600), 2 });
	_spawnChest.spawn = true;
	_spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(500, 500);
	
	_objectMgr->spawnObject(0x0001, Vector2(700, 500));
	_objectMgr->spawnObject(0x0001, Vector2(740, 500));
	_objectMgr->spawnObject(0x0002, Vector2(780, 500));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(1100, 600), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room21LR::release()
{
	Stage::release();
}

void Room21LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	if (KEY_MANAGER->isOnceKeyDown(VK_F8))
	{
		
		//_stageManager->moveRoom();
		
	}
}

void Room21LR::render()
{
	Stage::render();
}
