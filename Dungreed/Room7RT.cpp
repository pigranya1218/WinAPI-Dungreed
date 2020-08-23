#include "Room7RT.h"

void Room7RT::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage7_TR.map");


	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(400, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(500, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_GSWORD, Vector2(600, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_GSWORD, Vector2(800, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(1000, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(1150, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_NORMAL, Vector2(1300, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_NORMAL, Vector2(750, 600) });

	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(900, 700);

	_respawnPosition[1] = Vector2(900, 570);

	     
	
	makeDoor(Vector2(900, 475), DIRECTION::UP);

	_objectMgr->spawnObject(0x0000, Vector2(300, 200));
	_objectMgr->spawnObject(0x0000, Vector2(250, 200));
	_objectMgr->spawnObject(0x0001, Vector2(340, 200));
	
	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(500, 700), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room7RT::release()
{
Stage:: release();
}

void Room7RT::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room7RT::render()
{
	Stage::render();
	Image* torture1 = IMAGE_MANAGER->findImage("TortureTable0");
	torture1->setScale(4);
	torture1->render(CAMERA->getRelativeV2(Vector2(450, 290)));
	Image* torture2 = IMAGE_MANAGER->findImage("TortureTable1");
	torture2->setScale(4);
	torture2->render(CAMERA->getRelativeV2(Vector2(1150, 280)));
	Image* cell = IMAGE_MANAGER->findImage("BrokenCell");
	cell->setScale(4);
	cell->render(CAMERA->getRelativeV2(Vector2(850, 230)));
}
