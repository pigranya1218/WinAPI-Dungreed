#include "Room3LR.h"
#include "StageManager.h"

void Room3LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage3_LR.map");

	_respawnPosition[0] = Vector2(100,800);
	_respawnPosition[2] = Vector2(900, 400);

	_objectMgr->spawnObject(0x0000, Vector2(1700, 1300));

	_objectMgr->spawnObject(0x0001, Vector2(1300, 200));
	_objectMgr->spawnObject(0x0001, Vector2(700, 200));

	_objectMgr->spawnObject(0x0002, Vector2(800, 200));

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
