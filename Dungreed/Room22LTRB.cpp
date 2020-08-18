#include "Room22LTRB.h"

void Room22LTRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("Stage22LTRB.map");
}

void Room22LTRB::release()
{
	Stage::release();

}

void Room22LTRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);

}

void Room22LTRB::render()
{
	Stage::render();
}
