#include "Room4LRB.h"

void Room4LRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_LRB.map");

	//_respawnPosition[0] = Vector2(150,1300);
	
	//_respawnPosition[2] = Vector2(1600,1300);
	_respawnPosition[3] = Vector2(750, 1300);

	_objectMgr->spawnObject(0x0000, Vector2(1600, 1300));

	_objectMgr->spawnObject(0x0001, Vector2(500, 500));
	_objectMgr->spawnObject(0x0001, Vector2(600, 500));

	_objectMgr->spawnObject(0x0002, Vector2(650, 500));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(600, 600), DIRECTION::LEFT);
}

void Room4LRB::release()
{
	Stage::release();
}

void Room4LRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room4LRB::render()
{
	Stage::render();
}
