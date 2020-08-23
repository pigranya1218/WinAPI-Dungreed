#include "Room20LRB.h"

void Room20LRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage20_LB.map");

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

	_respawnPosition[3] = Vector2(400, 800);

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
	Stage::render();
}