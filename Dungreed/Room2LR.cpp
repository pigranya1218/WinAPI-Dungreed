#include "Room2LR.h"
#include "StageManager.h"

void Room2LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage2_LR.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(400, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(500, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 600) });
	_spawnChest.spawn = true;
	_spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(500, 500);

	//_respawnPosition[0] = Vector2(100, 450);
	//_respawnPosition[2] = Vector2(1100, 450);
	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(960, 430), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::CHEST_BLUE, Vector2(500, 430), DIRECTION::LEFT);

}

void Room2LR::release()
{
	Stage::release();
}

void Room2LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	if (KEY_MANAGER->isOnceKeyDown(VK_F8))
	{
		//_stageManager->moveRoom();

	}
}



void Room2LR::render()
{
	Stage::render();
}
