#include "Room11LT.h"

void Room11LT::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage11_LT.map");
	_respawnPosition[0] = Vector2(100, 600);

	_respawnPosition[1] = Vector2(800, 200);
	

}

void Room11LT::release()
{
	Stage::release();
}

void Room11LT::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room11LT::render()
{
	Stage::render();
}
