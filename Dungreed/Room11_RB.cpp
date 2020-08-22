#include "Room11_RB.h"

void Room11_RB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage11_RB.map");

	
	//_respawnPosition[2] = Vector2(1000, 600);
	_respawnPosition[3] = Vector2(450, 800);

	_objectMgr->spawnObject(0x0000, Vector2(600, 420));
	_objectMgr->spawnObject(0x0000, Vector2(550, 420));
	_objectMgr->spawnObject(0x0002, Vector2(650, 420));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(820, 420), DIRECTION::LEFT);
}

void Room11_RB::release()
{
	Stage::release();
}

void Room11_RB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room11_RB::render()
{
	Stage::render();
}
