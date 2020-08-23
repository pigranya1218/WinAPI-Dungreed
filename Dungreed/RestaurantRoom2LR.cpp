#include "RestaurantRoom2LR.h"

void RestaurantRoom2LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/RestaurantRoom2_LR.map");

	//_respawnPosition[0] = Vector2(300, 900);
	//_respawnPosition[2] = Vector2(2100, 900);

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(300, 660), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::RESTAURANT, Vector2(1100, 660), DIRECTION::LEFT);

	_roomType = ROOMTYPE::RESTAURANT;

	/*SOUND_MANAGER->stop("Floor1_BGM");
	SOUND_MANAGER->stop("FoodShop");
	SOUND_MANAGER->play("FoodShop", 1.0f);*/
}

void RestaurantRoom2LR::release()
{
	/*SOUND_MANAGER->stop("FoodShop");
	SOUND_MANAGER->stop("Floor1_BGM");
	SOUND_MANAGER->play("Floor1_BGM", 1.0f);*/
	Stage::release();
}

void RestaurantRoom2LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void RestaurantRoom2LR::render()
{
	for (int i = 0; i < _tile[0].tileX * _tile[0].tileY; ++i)
	{
		if (_tile[i].tileFrameX[0] != -1)
		{
			_tileImage->setScale(4);
			CAMERA->frameRender(_tileImage, _tile[i].rc.getCenter(), _tile[i].tileFrameX[0], _tile[i].tileFrameY[0]);
		}
		if (_tile[i].tileFrameX[1] != -1)
		{
			_tileImage->setScale(4);
			CAMERA->frameRender(_tileImage, _tile[i].rc.getCenter(), _tile[i].tileFrameX[1], _tile[i].tileFrameY[1]);
		}
	}

	int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;

	IMAGE_MANAGER->findImage("Tavern")->setScale(4);
	CAMERA->render(IMAGE_MANAGER->findImage("Tavern"), Vector2(stageWidth / 2, 586));

	_npcMgr->render();
	_enemyMgr->render();
	_objectMgr->render();
	_projectileMgr->render();
}
