#include "Room20LRB.h"

void Room20LRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage20_LRB.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(600, 1100) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(800, 1100) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(700, 1100) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(400, 1100) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(300, 1100) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_BIG_ICE, Vector2(350, 1100) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(750, 1100) });

	_spawnEnemies.push_back({ ENEMY_TYPE::BANSHEE, Vector2(670, 1490) });
	_spawnEnemies.push_back({ ENEMY_TYPE::MINOTAURS, Vector2(400, 2100) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_GIANT_RED, Vector2(670, 1670) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(380, 1650) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(970, 1650) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(600, 2100) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(800, 2100) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(700, 2100) });
	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(600, 2100);

	//_respawnPosition[3] = Vector2(400, 800);

	_objectMgr->spawnObject(0x0000, Vector2(300, 500));
	_objectMgr->spawnObject(0x0001, Vector2(350, 500));
	_objectMgr->spawnObject(0x0002, Vector2(450, 500));

	_objectMgr->spawnObject(0x0000, Vector2(220, 800));
	_objectMgr->spawnObject(0x0001, Vector2(270, 800));


	_objectMgr->spawnObject(0x0002, Vector2(800, 2500));

	_objectMgr->spawnObject(0x0000, Vector2(840, 2500));
	_objectMgr->spawnObject(0x0001, Vector2(880, 2500));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(900, 350), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room20LRB::release()
{
	Stage::release();
}

void Room20LRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	if (KEY_MANAGER->isOnceKeyDown(VK_F8))
	{

		//_stageManager->moveRoom();

	}
}

void Room20LRB::render()
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


	Image* table = IMAGE_MANAGER->findImage("TortureTable1");
	table->setScale(4);
	table->render(CAMERA->getRelativeV2(Vector2(1200, 1110)));

	Image* cell = IMAGE_MANAGER->findImage("BrokenCell");
	cell->setScale(4);
	cell->render(CAMERA->getRelativeV2(Vector2(300, 2094)));

	_npcMgr->render();
	_enemyMgr->render();
	_objectMgr->render();
	_projectileMgr->render();
}