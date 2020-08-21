#include "Room12LB.h"

void Room12LB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage12_LB.map");

	//_respawnPosition[0] = Vector2(230, 980);

	
	_respawnPosition[3] = Vector2(630, 960);

	_objectMgr->spawnObject(0x0000, Vector2(600, 200));
	_objectMgr->spawnObject(0x0001, Vector2(550, 200));
	_objectMgr->spawnObject(0x0002, Vector2(650, 200));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(550, 600), DIRECTION::LEFT);
}

void Room12LB::release()
{
	Stage::release();
}

void Room12LB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room12LB::render()
{
	Stage::render();
}
