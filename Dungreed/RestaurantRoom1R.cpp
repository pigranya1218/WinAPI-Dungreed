#include "RestaurantRoom1R.h"

void RestaurantRoom1R::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/RestaurantRoom2_R.map");

//	_respawnPosition[2] = Vector2(1000, 600);

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(450, 560), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::RESTAURANT, Vector2(850, 760), DIRECTION::LEFT);

	_roomType = ROOMTYPE::RESTAURANT;

	/*SOUND_MANAGER->stop("Floor1_BGM");
	SOUND_MANAGER->stop("FoodShop");
	SOUND_MANAGER->play("FoodShop", 1.0f);*/
}

void RestaurantRoom1R::release()
{
	/*SOUND_MANAGER->stop("FoodShop");
	SOUND_MANAGER->stop("Floor1_BGM");
	SOUND_MANAGER->play("Floor1_BGM", 1.0f);*/
	Stage::release();
}

void RestaurantRoom1R::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void RestaurantRoom1R::render()
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
	CAMERA->render(IMAGE_MANAGER->findImage("Tavern"), Vector2(stageWidth / 2, 580));

	_npcMgr->render();
	_enemyMgr->render();
	_objectMgr->render();
	_projectileMgr->render();
}
