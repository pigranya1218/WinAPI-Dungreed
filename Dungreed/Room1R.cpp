#include "Room1R.h"
#include "StageManager.h"

void Room1R::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/Stage1_R.map");

	//_respawnPosition[2] = Vector2(1750,500);

	_objectMgr->spawnObject(0x0000, Vector2(550, 600));

	_objectMgr->spawnObject(0x0001, Vector2(320, 600));
	_objectMgr->spawnObject(0x0001, Vector2(450, 600));
	//_objectMgr->spawnObject(0x0001, Vector2(430, 600));

	_objectMgr->spawnObject(0x0002, Vector2(400, 600));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(600, 600), DIRECTION::LEFT);
}

void Room1R::release()
{
	Stage::release();
}

void Room1R::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void Room1R::render()
{
	Stage::render();
}
