#include "Room4LR.h"
#include "StageManager.h"

void Room4LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage4LR.map");
	_OpenDirection[0] = true;
	_OpenDirection[1] = false;
	_OpenDirection[2] = true;
	_OpenDirection[3] = false;
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
