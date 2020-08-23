#include "Room3LR.h"
#include "StageManager.h"

void Room3LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage3_LR.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(400, 300) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(1300, 300) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(2200, 300) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BANSHEE, Vector2(1280, 1200) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(1000, 1300) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(1400, 1300) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_RED, Vector2(900, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_RED, Vector2(1150, 700) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_RED, Vector2(1300, 700) });

	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(WINSIZEX / 2 - 300,  WINSIZEY / 2 + 600) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(2200,  WINSIZEY / 2 + 600) });

	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if(boxPer%5==1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;
	
	if(randBox%10==1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if(randBox%3==1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(1200, 700);

	_objectMgr->spawnObject(0x0000, Vector2(1700, 1300));

	_objectMgr->spawnObject(0x0001, Vector2(1300, 200));
	_objectMgr->spawnObject(0x0001, Vector2(700, 200));

	_objectMgr->spawnObject(0x0002, Vector2(800, 200));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(1150, 800), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::CHEST_YELLOW, Vector2(1400, 800), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room3LR::release()
{
	Stage::release();
}

void Room3LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	if (KEY_MANAGER->isOnceKeyDown(VK_F8))
	{
		//_stageManager->moveRoom();
		
	}
}

void Room3LR::render()
{
	Stage::render();
}
