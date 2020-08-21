#include "RestaurantRoom1R.h"

void RestaurantRoom1R::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/RestaurantRoom1_R.map");

	_respawnPosition[2] = Vector2(1000, 600);
}

void RestaurantRoom1R::release()
{
	Stage::release();
}

void RestaurantRoom1R::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void RestaurantRoom1R::render()
{
	Stage::render();
}
