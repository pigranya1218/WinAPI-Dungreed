#include "Room7_RB.h"

void Room7_RB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage7_RB.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(400, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(500, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_GSWORD, Vector2(600, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_GSWORD, Vector2(800, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(1000, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(1150, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_RED, Vector2(1300, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_RED, Vector2(750, 600) });


	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(900, 700);

	//_respawnPosition[2] = Vector2(1000, 400);
	_respawnPosition[3] = Vector2(860, 700);

	_objectMgr->spawnObject(0x0000, Vector2(300, 200));
	_objectMgr->spawnObject(0x0000, Vector2(250, 200));
	_objectMgr->spawnObject(0x0001, Vector2(400, 500));
	//_objectMgr->spawnObject(0x0001, Vector2(400, 200));
	//
	_objectMgr->spawnObject(0x0002, Vector2(300, 500));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(500, 700), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room7_RB::release()
{
	Stage::release();
}

void Room7_RB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room7_RB::render()
{
	D2D_RENDERER->fillRectangle(FloatRect(0, 0, TILESIZE * 30, TILESIZE * 20), 51, 49, 67, 1);
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


	Image* torture1 = IMAGE_MANAGER->findImage("TortureTable0");
	torture1->setScale(4);
	torture1->render(CAMERA->getRelativeV2(Vector2(450, 290)));
	Image* torture2 = IMAGE_MANAGER->findImage("TortureTable1");
	torture2->setScale(4);
	torture2->render(CAMERA->getRelativeV2(Vector2(1150, 280)));
	Image* cell = IMAGE_MANAGER->findImage("BrokenCell");
	cell->setScale(4);
	cell->render(CAMERA->getRelativeV2(Vector2(850, 230)));

	_npcMgr->render();
	_enemyMgr->render();
	_objectMgr->render();
	_projectileMgr->render();
}
