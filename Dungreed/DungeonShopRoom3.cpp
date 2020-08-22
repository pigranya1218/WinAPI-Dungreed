#include "DungeonShopRoom3.h"

void DungeonShopRoom3::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/DungeonShopRoom1_LR.map");

	//_respawnPosition[0] = Vector2(240, 500);
	//_respawnPosition[2] = Vector2(1600, 500);

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(600, 250), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::SHOP, Vector2(800, 650), DIRECTION::LEFT);

	_roomType = ROOMTYPE::SHOP;
}

void DungeonShopRoom3::release()
{
	Stage::release();
}

void DungeonShopRoom3::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void DungeonShopRoom3::render()
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

	IMAGE_MANAGER->findImage("InDungeonShop")->setScale(4);
	CAMERA->render(IMAGE_MANAGER->findImage("InDungeonShop"), Vector2(1150, 708));

	_npcMgr->render();
	_enemyMgr->render();
	_objectMgr->render();
	_projectileMgr->render();
}
