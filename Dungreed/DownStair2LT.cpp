#include "DownStair2LT.h"

void DownStair2LT::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/DownStair2_LT.map");


	_gateImg = IMAGE_MANAGER->findImage("Floor1Door");

	//_respawnPosition[0] = Vector2(120, 480);
	//_respawnPosition[1] = Vector2(630, 300);

	_objectMgr->spawnObject(0x0001, Vector2(700, 500));
	_objectMgr->spawnObject(0x0001, Vector2(740, 500));
	_objectMgr->spawnObject(0x0002, Vector2(780, 500));

	_npcMgr->spawnNpc(NPC_TYPE::EXIT, Vector2(550, 1030), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(550, 435), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void DownStair2LT::release()
{
	Stage::release();
}

void DownStair2LT::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void DownStair2LT::render()
{
	Stage::render();
}
