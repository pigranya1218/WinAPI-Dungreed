#include "Room4LR.h"
#include "StageManager.h"

void Room4LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_LR.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400), 1 });
		_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500), 1 });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600), 1 });
	_spawnChest.spawn = true;
	_spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(500, 500);

	_objectMgr->spawnObject(0x0000, Vector2(1600, 1300));

	_objectMgr->spawnObject(0x0001, Vector2(500, 500));
	_objectMgr->spawnObject(0x0001, Vector2(600, 500));

	_objectMgr->spawnObject(0x0002, Vector2(650, 500));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(1000, 1320), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room4LR::release()
{
	Stage::release();
}

void Room4LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	if (KEY_MANAGER->isOnceKeyDown(VK_F8))
	{
		//_stageManager->moveRoom();
		_stageManager->makeStage();
	}
}

void Room4LR::render()
{
	Stage::render();
}
