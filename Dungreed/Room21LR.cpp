#include "Room21LR.h"
#include "StageManager.h"

void Room21LR::init()
{

    Stage:: init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage21_LR.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(800, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(900, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_GSWORD, Vector2(750, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_GIANT_RED, Vector2(1000, 450) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_ICE, Vector2(600, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_ICE, Vector2(780, 500) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_NORMAL, Vector2(720, 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_NORMAL, Vector2(800, 450) });
	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if (boxPer % 5 == 1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;

	if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(500, 500);

	_objectMgr->spawnObject(0x0001, Vector2(700, 700));
	_objectMgr->spawnObject(0x0001, Vector2(740, 700));
	_objectMgr->spawnObject(0x0002, Vector2(780, 700));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(1100, 680), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room21LR::release()
{
	Stage::release();
}

void Room21LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	if (KEY_MANAGER->isOnceKeyDown(VK_F8))
	{
		
		//_stageManager->moveRoom();
		
	}
}

void Room21LR::render()
{
	Stage::render();
}
