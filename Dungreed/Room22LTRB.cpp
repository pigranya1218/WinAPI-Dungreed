#include "Room22LTRB.h"
#include "StageManager.h"

void Room22LTRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage22LTRB.map");
	_OpenDirection[0] = true;
	_OpenDirection[1] = true;
	_OpenDirection[2] = true;
	_OpenDirection[3] = true;

}

void Room22LTRB::release()
{
	Stage::release();

}

void Room22LTRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	if (KEY_MANAGER->isOnceKeyDown(VK_F8))
	{
		
		//_stageManager->moveRoom();
		
		
	}
}

void Room22LTRB::render()
{
	Stage::render();
}
