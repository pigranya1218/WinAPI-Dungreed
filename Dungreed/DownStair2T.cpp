#include "DownStair2T.h"

void DownStair2T::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/DownStair2_T.map");

	//_respawnPosition[1] = Vector2(500, 300);

	_objectMgr->spawnObject(0x0001, Vector2(700, 500));
	_objectMgr->spawnObject(0x0001, Vector2(740, 500));
	_objectMgr->spawnObject(0x0002, Vector2(780, 500));

	_objectMgr->spawnObject(0x0000, Vector2(700, 900));
	_objectMgr->spawnObject(0x0000, Vector2(740, 900));
	_objectMgr->spawnObject(0x0001, Vector2(780, 900));

}

void DownStair2T::release()
{
	Stage::release();
}

void DownStair2T::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void DownStair2T::render()
{
	Stage::render();
}
