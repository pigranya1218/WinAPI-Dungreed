#include "Room21LR.h"
#include "StageManager.h"

void Room21LR::init()
{

    Stage:: init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage21_LR.map");
	//_respawnPosition[0] = Vector2(200, 1000);
	
	//_respawnPosition[2] = Vector2(1500, 600);
	
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
