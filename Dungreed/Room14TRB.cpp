#include "Room14TRB.h"

void Room14TRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage14_TRB.map");

	//_respawnPosition[1] = Vector2(600, 400);
	//_respawnPosition[2] = Vector2(1000, 900);
	_respawnPosition[3] = Vector2(1500, 930);

	_objectMgr->spawnObject(0x0000, Vector2(300, 500));
	_objectMgr->spawnObject(0x0001, Vector2(350, 500));
	_objectMgr->spawnObject(0x0002, Vector2(450, 500));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(1300, 1000), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room14TRB::release()
{
	Stage::release();
}

void Room14TRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room14TRB::render()
{
	Stage::render();
}
