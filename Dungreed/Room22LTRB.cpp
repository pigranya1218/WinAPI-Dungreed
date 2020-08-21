#include "Room22LTRB.h"
#include "StageManager.h"

void Room22LTRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage22_LTRB.map");
	
	//_respawnPosition[0] = Vector2(200, 200);
	//_respawnPosition[1] = Vector2(400, 200);
	//_respawnPosition[2] = Vector2(1500, 200);
	//_respawnPosition[3] = Vector2(400, 800);

	_objectMgr->spawnObject(0x0001, Vector2(700, 500));
	_objectMgr->spawnObject(0x0001, Vector2(740, 500));
	_objectMgr->spawnObject(0x0002, Vector2(780, 500));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(600, 600), DIRECTION::LEFT);
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
