#include "Room4LTR.h"

void Room4LTR::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_LTR.map");
	//_respawnPosition[0] = Vector2(150, 1300);

	//_respawnPosition[1] = Vector2(780, 200);
	//_respawnPosition[2] = Vector2(1600, 1000);

	_objectMgr->spawnObject(0x0000, Vector2(1600, 1300));

	_objectMgr->spawnObject(0x0001, Vector2(500, 500));
	_objectMgr->spawnObject(0x0001, Vector2(900, 1000));

	_objectMgr->spawnObject(0x0002, Vector2(650, 1000));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(600, 600), DIRECTION::LEFT);
}

void Room4LTR::release()
{
	Stage::release();
}

void Room4LTR::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room4LTR::render()
{
	Stage::render();
}
