#include "Room3LR.h"
#include "StageManager.h"

void Room3LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage3_LR.map");


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
