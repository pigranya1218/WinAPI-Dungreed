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
	Stage::render();

	int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;
	IMAGE_MANAGER->findImage("Tavern")->setScale(4);
	CAMERA->render(IMAGE_MANAGER->findImage("Tavern"), Vector2(stageWidth / 2, 580));
}
