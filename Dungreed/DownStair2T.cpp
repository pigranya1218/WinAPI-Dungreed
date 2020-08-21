#include "DownStair2T.h"

void DownStair2T::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/DownStair2_T.map");

	_respawnPosition[1] = Vector2(500, 300);

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
