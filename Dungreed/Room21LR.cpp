#include "Room21LR.h"
#include "StageManager.h"

void Room21LR::init()
{

    Stage:: init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage21_LR.map");
	_respawnPosition[0] = Vector2(200, 200);
	
	_respawnPosition[2] = Vector2(900, 200);
	
	_objectMgr->spawnObject(0x0001, Vector2(700, 500));
	_objectMgr->spawnObject(0x0001, Vector2(740, 500));
	_objectMgr->spawnObject(0x0002, Vector2(780, 500));

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
