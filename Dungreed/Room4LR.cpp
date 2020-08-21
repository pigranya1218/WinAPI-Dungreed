#include "Room4LR.h"
#include "StageManager.h"

void Room4LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_LR.map");
	//_respawnPosition[0] = Vector2(150, 1300);
	//_respawnPosition[2] = Vector2(1600, 1300);

	_objectMgr->spawnObject(0x0000, Vector2(1600, 1300));

	_objectMgr->spawnObject(0x0001, Vector2(500, 500));
	_objectMgr->spawnObject(0x0001, Vector2(600, 500));

	_objectMgr->spawnObject(0x0002, Vector2(650, 500));

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
