#include "DownStair2LT.h"

void DownStair2LT::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/DownStair2_LT.map");

	//_respawnPosition[0] = Vector2(120, 480);
	//_respawnPosition[1] = Vector2(630, 300);

	_objectMgr->spawnObject(0x0001, Vector2(700, 500));
	_objectMgr->spawnObject(0x0001, Vector2(740, 500));
	_objectMgr->spawnObject(0x0002, Vector2(780, 500));

}

void DownStair2LT::release()
{
	Stage::release();
}

void DownStair2LT::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void DownStair2LT::render()
{
	Stage::render();
}
