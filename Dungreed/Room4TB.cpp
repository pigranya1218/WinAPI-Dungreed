#include "Room4TB.h"

void Room4TB::init()
{
	Stage::init();
	
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_TB.map");


	_objectMgr->spawnObject(0x0000, Vector2(1600, 1300));

	_objectMgr->spawnObject(0x0001, Vector2(500, 500));
	_objectMgr->spawnObject(0x0001, Vector2(600, 500));

	_objectMgr->spawnObject(0x0002, Vector2(650, 500));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(1000, 1320), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::CHEST_BOSS, Vector2(1000, 620), DIRECTION::LEFT);
}

void Room4TB::release()
{
	Stage::release();
}

void Room4TB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room4TB::render()
{
	Stage::render();
}
