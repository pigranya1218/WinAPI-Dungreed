#include "Room23LR.h"

void Room23LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage23_LR.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_BOMB, Vector2(950, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_BOMB, Vector2(1250, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BANSHEE, Vector2(650, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BANSHEE, Vector2(1450, 400) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(600, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(700, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(800, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(900, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(1000, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(1100, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(1200, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(1300, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(1400, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::GHOST, Vector2(1500, 500) });
	
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(650, 650),2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(1450, 650),2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(670, 900),2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(1430, 900),2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(740, 900),2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(1300, 900),2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_GSWORD, Vector2(640, 900),2 });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_GSWORD, Vector2(1390, 900),2 });

	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(1090, 900);

	_objectMgr->spawnObject(0x0001, Vector2(700, 650));
	_objectMgr->spawnObject(0x0001, Vector2(740, 650));
	_objectMgr->spawnObject(0x0002, Vector2(780, 670));

	_objectMgr->spawnObject(0x0000, Vector2(1100, 900));
	_objectMgr->spawnObject(0x0000, Vector2(1140, 900));
	_objectMgr->spawnObject(0x0001, Vector2(1180, 900));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(600, 600), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room23LR::release()
{
	Stage::release();
}

void Room23LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room23LR::render()
{
	
	Image* cell = IMAGE_MANAGER->findImage("UpperCell0");
	cell->setScale(4);
	cell->render(CAMERA->getRelativeV2(Vector2(1050, 370)));

	_npcMgr->render();
	_enemyMgr->render();
	_objectMgr->render();
	_projectileMgr->render();
}
