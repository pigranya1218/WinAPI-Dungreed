#include "Room1R.h"
#include "StageManager.h"

void Room1R::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage1_R.map");

	
	//Έχ ΌÒΘ―
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_GIANT_RED, Vector2(700, 450) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_GIANT_NORMAL, Vector2(1000, 450) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_NORMAL, Vector2(500, 300) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_RED, Vector2(1100, 750) });
	_spawnEnemies.push_back({ ENEMY_TYPE::BAT_RED, Vector2(730, 720) });

	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(600, 850) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(750, 850) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_DOG, Vector2(900, 850) });

	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(450, 850) });
	_spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_DAGGER, Vector2(1050, 850) });

	_spawnChest.spawn = true;
	_spawnChest.type = NPC_TYPE::CHEST_BASIC;
	_spawnChest.pos = Vector2(850, 900);

	_objectMgr->spawnObject(0x0000, Vector2(550, 600));

	_objectMgr->spawnObject(0x0001, Vector2(320, 800));
	_objectMgr->spawnObject(0x0001, Vector2(450, 800));
	//_objectMgr->spawnObject(0x0001, Vector2(430, 600));

	_objectMgr->spawnObject(0x0002, Vector2(400, 800));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(600, 800), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::CHEST_BASIC, Vector2(400, 800), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room1R::release()
{
	Stage::release();
}

void Room1R::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room1R::render()
{
	Stage::render();
}
