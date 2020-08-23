#include "Room10T.h"
#include "StageManager.h"

void Room10T::init()
{
   Stage::init();
   _tileImage = IMAGE_MANAGER->findImage("sampleTile1");
   loadMap("room/Stage10_T.map");

   _spawnEnemies.push_back({ ENEMY_TYPE::SKEL_MAGICIAN_ICE, Vector2(350, 400) });
   _spawnEnemies.push_back({ ENEMY_TYPE::SKEL_MAGICIAN_ICE, Vector2(1200, 400) });
   _spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(600, 400) });
   _spawnEnemies.push_back({ ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(900, 400) });
   _spawnEnemies.push_back({ ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(600, 600) });
   _spawnEnemies.push_back({ ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(870, 600) });

   int randBox = RANDOM->getInt(10);
   int boxPer = RANDOM->getInt(10);
   if (boxPer % 5 == 1)_spawnChest.spawn = false;
   else _spawnChest.spawn = true;

   if (randBox % 10 == 1)_spawnChest.type = NPC_TYPE::CHEST_YELLOW;
   else if (randBox % 3 == 1)_spawnChest.type = NPC_TYPE::CHEST_BLUE;
   else _spawnChest.type = NPC_TYPE::CHEST_BASIC;
   _spawnChest.pos = Vector2(770, 600);

   //_respawnPosition[1] = Vector2(700, 250);

   _npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(350, 400), DIRECTION::LEFT);

   _roomType = ROOMTYPE::NORMAL;
}

void Room10T::release()
{
	Stage::release();
}

void Room10T::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room10T::render()
{
	Stage::render();
}
