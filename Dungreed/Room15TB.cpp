#include "Room15TB.h"

void Room15TB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage15_TB.map");

	_respawnPosition[3] = Vector2(490, 1120);

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(800, 1000), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void Room15TB::release()
{
	Stage::release();
}

void Room15TB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room15TB::render()
{
	Stage::render();
}
