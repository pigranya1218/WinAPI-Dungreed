#include "Room2LR.h"
#include "StageManager.h"

void Room2LR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage2_LR.map");

	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(370, 310) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(370, 610) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(370, 910) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(1600, 510) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(1600, 610) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(1600, 710) });


	int randBox = RANDOM->getInt(10);
	int boxPer = RANDOM->getInt(10);
	if(boxPer%5==1)_spawnChest.spawn = false;
	else _spawnChest.spawn = true;
	
	if(randBox%10==1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
	else if(randBox%3==1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
	else _spawnChest.type = NPC_TYPE::CHEST_BASIC;

	_spawnChest.pos = Vector2(910, 400);

	//_respawnPosition[0] = Vector2(100, 450);
	//_respawnPosition[2] = Vector2(1100, 450);
	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(960, 430), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::CHEST_BLUE, Vector2(500, 430), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room2LR::release()
{
	Stage::release();
}

void Room2LR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	if (KEY_MANAGER->isOnceKeyDown(VK_F8))
	{
		//_stageManager->moveRoom();

	}
}



void Room2LR::render()
{
	Stage::render();
}
