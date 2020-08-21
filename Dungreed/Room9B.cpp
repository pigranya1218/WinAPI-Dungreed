#include "Room9B.h"
#include "StageManager.h"

void Room9B::init()
{
	Stage::init(); 
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage9_B.map");
	
	_respawnPosition[3] = Vector2(500, 600);
	makeDoor(Vector2(600, 800), DIRECTION::DOWN);

	_objectMgr->spawnObject(0x0000, Vector2(600, 200));
	_objectMgr->spawnObject(0x0000, Vector2(550, 200));
	_objectMgr->spawnObject(0x0002, Vector2(650, 200));
}

void Room9B::release()
{
	Stage::release();
}

void Room9B::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room9B::render()
{
	Stage::render();
}
