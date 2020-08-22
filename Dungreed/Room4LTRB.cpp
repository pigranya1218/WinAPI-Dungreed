#include "Room4LTRB.h"

void Room4LTRB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage4_LTRB.map");
	//_respawnPosition[0] = Vector2(150, 1300);
	//_respawnPosition[1] = Vector2(750,200);
	//_respawnPosition[2] = Vector2(1600, 1300);
	_respawnPosition[3] = Vector2(750, 1300);

	_objectMgr->spawnObject(0x0001, Vector2(900, 500));
	//_objectMgr->spawnObject(0x0001, Vector2(900, 1000));
	//
	_objectMgr->spawnObject(0x0002, Vector2(820, 500));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(600, 600), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room4LTRB::release()
{
	Stage::release();
}

void Room4LTRB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room4LTRB::render()
{
	Stage::render();
}
