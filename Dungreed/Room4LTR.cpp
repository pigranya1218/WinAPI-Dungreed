#include "Room4LTR.h"

void Room4LTR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_LTR.map");
	_respawnPosition[0] = Vector2(200, 600);

	_respawnPosition[1] = Vector2(400, 200);
	_respawnPosition[2] = Vector2(650, 700);
}

void Room4LTR::release()
{
	Stage::release();
}

void Room4LTR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room4LTR::render()
{
	Stage::render();
}
