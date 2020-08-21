#include "StartRoom2.h"

void StartRoom2::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/StartRoom2_RB.map");

	
	_respawnPosition[0] = Vector2(580, 600);
	_respawnPosition[1] = Vector2(600, 600);
	_respawnPosition[3] = Vector2(600, 600);

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
