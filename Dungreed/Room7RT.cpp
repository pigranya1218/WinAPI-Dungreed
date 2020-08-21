#include "Room7RT.h"

void Room7RT::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage7_TR.map");
	_respawnPosition[1] = Vector2(900, 570);

	_respawnPosition[2] = Vector2(1550, 600);          
	
	makeDoor(Vector2(900, 475), DIRECTION::UP);
}

void Room7RT::release()
{
Stage:: release();
}

void Room7RT::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room7RT::render()
{
	Stage::render();
}
