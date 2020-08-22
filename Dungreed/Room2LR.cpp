#include "Room2LR.h"
#include "StageManager.h"

void Room2LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage2_LR.map");

	//_respawnPosition[0] = Vector2(100, 450);
	//_respawnPosition[2] = Vector2(1100, 450);
	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(960, 440), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::CHEST_BLUE, Vector2(400, 440), DIRECTION::LEFT);

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
