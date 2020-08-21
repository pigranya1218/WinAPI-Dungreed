#include "Room13LTB.h"

void Room13LTB::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage13_LTB.map");

	//_respawnPosition[0] = Vector2(200, 450);
	//_respawnPosition[1] = Vector2(640, 300);
	_respawnPosition[3] = Vector2(300, 800);
	
	makeDoor(Vector2(309, 1100), DIRECTION::DOWN);

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(520, 700), DIRECTION::LEFT);
}

void Room13LTB::release()
{
	Stage::release();
}

void Room13LTB::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room13LTB::render()
{
	Stage::render();
}
