#include "Room14TRB.h"

void Room14TRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage14_TRB.map");

	_respawnPosition[1] = Vector2(600, 400);
	_respawnPosition[2] = Vector2(1000, 900);
	_respawnPosition[3] = Vector2(850, 900);

	_objectMgr->spawnObject(0x0000, Vector2(300, 500));
	_objectMgr->spawnObject(0x0001, Vector2(350, 500));
	_objectMgr->spawnObject(0x0002, Vector2(450, 500));
}

void Room14TRB::release()
{
	Stage::release();
}

void Room14TRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room14TRB::render()
{
	Stage::render();
}
