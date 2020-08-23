#include "RestaurantRoom.h"

void RestaurantRoom::init()
{


	Stage::init();

	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/RestaurantRoom2_L.map");
	//_respawnPosition[0] = Vector2(200, 600);

	//makeDoor(Vector2(100,850), DIRECTION::LEFT);

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(400, 560), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::RESTAURANT, Vector2(700, 860), DIRECTION::LEFT);

	_roomType = ROOMTYPE::RESTAURANT;

	/*SOUND_MANAGER->stop("Floor1_BGM");
	SOUND_MANAGER->stop("Foodshop");
	SOUND_MANAGER->play("Foodshop",1.0f);*/
}
 
void RestaurantRoom::release()
{
	//SOUND_MANAGER->stop("Foodshop");
	/*SOUND_MANAGER->stop("Floor1_BGM");
	SOUND_MANAGER->play("Floor1_BGM", 1.0f);*/
	Stage::release();
}

void RestaurantRoom::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void RestaurantRoom::render()
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
	CAMERA->render(IMAGE_MANAGER->findImage("Tavern"), Vector2(stageWidth / 2, 640));

	_npcMgr->render();
	_enemyMgr->render();
	_objectMgr->render();
	_projectileMgr->render();
}
