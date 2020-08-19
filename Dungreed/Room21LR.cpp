#include "Room21LR.h"
#include "StageManager.h"

void Room21LR::init()
{

    Stage:: init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage21LR.map");
	_OpenDirection[0] = true;
	_OpenDirection[1] = false;
	_OpenDirection[2] = true;
	_OpenDirection[3] = false;

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
		
		_stageManager->moveRoom();
		
	}
}

void Room21LR::render()
{
	Stage::render();
}
