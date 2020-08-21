#include "Room7_RB.h"

void Room7_RB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage7_RB.map");

	

	_respawnPosition[2] = Vector2(1000, 400);
	_respawnPosition[3] = Vector2(300, 900);

	_objectMgr->spawnObject(0x0000, Vector2(300, 200));
	_objectMgr->spawnObject(0x0000, Vector2(250, 200));
	_objectMgr->spawnObject(0x0001, Vector2(400, 500));
	//_objectMgr->spawnObject(0x0001, Vector2(400, 200));
	//
	_objectMgr->spawnObject(0x0002, Vector2(300, 500));
}

void Room7_RB::release()
{
	Stage::release();
}

void Room7_RB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room7_RB::render()
{
	Stage::render();
}
