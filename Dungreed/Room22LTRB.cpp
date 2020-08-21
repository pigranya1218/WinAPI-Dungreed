#include "Room22LTRB.h"
#include "StageManager.h"

void Room22LTRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage22_LTRB.map");
	
	_respawnPosition[0] = Vector2(200, 200);
	_respawnPosition[1] = Vector2(400, 200);
	_respawnPosition[2] = Vector2(1500, 200);
	_respawnPosition[3] = Vector2(400, 800);
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
