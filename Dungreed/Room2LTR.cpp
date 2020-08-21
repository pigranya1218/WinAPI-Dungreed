#include "Room2LTR.h"
#include "StageManager.h"

void Room2LTR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage2_LR.map");
	_OpenDirection[0] = true;
	_OpenDirection[1] = true;
	_OpenDirection[2] = true;
	_OpenDirection[3] = false;

}

void Room2LTR::release()
{
	Stage::release();
}

void Room2LTR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	if (KEY_MANAGER->isOnceKeyDown(VK_F8))
	{
		//_stageManager->moveRoom();
		
	}
}

void Room2LTR::render()
{
	Stage::render();
}
