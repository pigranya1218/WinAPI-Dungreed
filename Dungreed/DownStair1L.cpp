#include "DownStair1L.h"

void DownStair1L::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/DownStair1_L.map");
	
	_gateImg = IMAGE_MANAGER->findImage("Floor1Door");

	//_respawnPosition[0] = Vector2(200, 600);

	_objectMgr->spawnObject(0x0001, Vector2(940, 650));
	_objectMgr->spawnObject(0x0001, Vector2(980, 650));
	_objectMgr->spawnObject(0x0002, Vector2(1040, 650));

	/*_objectMgr->spawnObject(0x0000, Vector2(1200, 500));
	_objectMgr->spawnObject(0x0000, Vector2(1140, 500));
	_objectMgr->spawnObject(0x0001, Vector2(1080, 500));*/

	_npcMgr->spawnNpc(NPC_TYPE::EXIT, Vector2(700, 650), DIRECTION::LEFT);
	//_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(380, 650), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void DownStair1L::release()
{
	Stage::release();
}

void DownStair1L::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void DownStair1L::render()
{
	Stage::render();
}
