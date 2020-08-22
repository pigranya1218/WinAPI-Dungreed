#include "Room8L.h"
#include "StageManager.h"

void Room8L::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage8_L.map");
	//_respawnPosition[0] = Vector2(160, 680);

	_objectMgr->spawnObject(0x0000, Vector2(1200, 810));
	_objectMgr->spawnObject(0x0000, Vector2(1240, 810));
	_objectMgr->spawnObject(0x0001, Vector2(1280, 810));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(570, 810), DIRECTION::LEFT);
}

void Room8L::release()
{
	Stage::release();
}

void Room8L::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room8L::render()
{
	Stage::render();
}
