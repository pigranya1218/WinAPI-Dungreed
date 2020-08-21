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

	int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;
	IMAGE_MANAGER->findImage("Tavern")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("Tavern"), Vector2(stageWidth / 2, 760));
}
