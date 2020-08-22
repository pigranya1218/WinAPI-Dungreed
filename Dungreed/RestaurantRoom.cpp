#include "RestaurantRoom.h"

void RestaurantRoom::init()
{


	Stage::init();

	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/RestaurantRoom2_L.map");
	//_respawnPosition[0] = Vector2(200, 600);

	//makeDoor(Vector2(100,850), DIRECTION::LEFT);

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(400, 660), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::RESTAURANT, Vector2(850, 660), DIRECTION::LEFT);
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

	IMAGE_MANAGER->findImage("Tavern")->setScale(4);
	CAMERA->render(IMAGE_MANAGER->findImage("Tavern"), Vector2(stageWidth / 2, 430));
	
}
