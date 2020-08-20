#include "RestaurantRoom2LR.h"

void RestaurantRoom2LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("RestaurantRoom2LR.map");
}

void RestaurantRoom2LR::release()
{
	Stage::release();
}

void RestaurantRoom2LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void RestaurantRoom2LR::render()
{
	Stage::render();
	for (int i = 0; i < _collisionGroundRects.size(); i++)
	{
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_collisionGroundRects[i]), D2D1::ColorF::Enum::Red, 1, 1);
	}

	for (int i = 0; i < _collisionGroundLines.size(); i++)
	{
		D2D_RENDERER->drawLine(CAMERA->getRelativeV2(_collisionGroundLines[i].getStart()), CAMERA->getRelativeV2(_collisionGroundLines[i].getEnd()), D2D1::ColorF::Enum::Red, 1);
	}

	for (int i = 0; i < _collisionPlatforms.size(); i++)
	{
		D2D_RENDERER->drawLine(CAMERA->getRelativeV2(_collisionPlatforms[i].getStart()), CAMERA->getRelativeV2(_collisionPlatforms[i].getEnd()), D2D1::ColorF::Enum::Blue, 1);
	}

	int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;

	IMAGE_MANAGER->findImage("Tavern")->setScale(5);
	CAMERA->render(IMAGE_MANAGER->findImage("Tavern"), Vector2(stageWidth / 2, 760));
}