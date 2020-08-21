#include "StartRoom2.h"

void StartRoom2::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/StartRoom2_RB.map");

	
	_respawnPosition[0] = Vector2(565, 670);

	/*_respawnPosition[2] = Vector2(1450, 670);
	_respawnPosition[3] = Vector2(1200, 670);*/
	/*makeDoor(Vector2(TILESIZE * 24 + TILESIZE * 0.5, TILESIZE * 9), DIRECTION::RIGHT);
	makeDoor(Vector2(TILESIZE * 19, TILESIZE * 14 + TILESIZE * 0.5), DIRECTION::DOWN);*/	

	_objectMgr->spawnObject(0x0000, Vector2(500, 600));

	_objectMgr->spawnObject(0x0001, Vector2(200, 600));
	_objectMgr->spawnObject(0x0001, Vector2(380, 600));
	_objectMgr->spawnObject(0x0001, Vector2(430, 600));
	_objectMgr->spawnObject(0x0002, Vector2(300, 600));
}

void StartRoom2::release()
{
	Stage::release();
}

void StartRoom2::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void StartRoom2::render()
{
	Stage::render();
}
