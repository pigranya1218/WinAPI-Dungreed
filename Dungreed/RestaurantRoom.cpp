#include "RestaurantRoom.h"

void RestaurantRoom::init()
{


	Stage::init();

	
}

void RestaurantRoom::release()
{
	Stage::release();
}

void RestaurantRoom::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void RestaurantRoom::render()
{
	Stage::render();

	for (int i = 0; i < _collisionGrounds.size(); i++)
	{
		D2D_RENDERER->drawLine(CAMERA->getRelativeV2(_collisionGrounds[i].func.getStart()), CAMERA->getRelativeV2(_collisionGrounds[i].func.getEnd()), D2D1::ColorF::Enum::Red, 1);
	}

	for (int i = 0; i < _collisionPlatforms.size(); i++)
	{
		D2D_RENDERER->drawLine(CAMERA->getRelativeV2(_collisionPlatforms[i].func.getStart()), CAMERA->getRelativeV2(_collisionPlatforms[i].func.getEnd()), D2D1::ColorF::Enum::Blue, 1);
	}

	int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;

	IMAGE_MANAGER->findImage("Tavern")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("Tavern"), Vector2(stageWidth / 2, 760));
	
}
