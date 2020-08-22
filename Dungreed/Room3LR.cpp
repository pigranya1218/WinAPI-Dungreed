#include "Room3LR.h"
#include "StageManager.h"

void Room3LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage3_LR.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600) });
	_spawnChest.spawn = true;
	_spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(500, 500);

	_objectMgr->spawnObject(0x0000, Vector2(1700, 1300));

	_objectMgr->spawnObject(0x0001, Vector2(1300, 200));
	_objectMgr->spawnObject(0x0001, Vector2(700, 200));

	_objectMgr->spawnObject(0x0002, Vector2(800, 200));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(1150, 800), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::CHEST_YELLOW, Vector2(1400, 800), DIRECTION::LEFT);

}

void Room3LR::release()
{
	Stage::release();
}

void Room3LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	if (KEY_MANAGER->isOnceKeyDown(VK_F8))
	{
		//_stageManager->moveRoom();
		
	}
}

void Room3LR::render()
{
	Stage::render();
}
