#include "StartRoom2.h"

void StartRoom2::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/StartRoom2_RB.map");

	
	_respawnPosition[0] = Vector2(565, 650);

	//_respawnPosition[2] = Vector2(1450, 670);
	
	_respawnPosition[3] = Vector2(1200, 670);

	/*makeDoor(Vector2(TILESIZE * 24 + TILESIZE * 0.5, TILESIZE * 9), DIRECTION::RIGHT);
	makeDoor(Vector2(TILESIZE * 19, TILESIZE * 14 + TILESIZE * 0.5), DIRECTION::DOWN);*/	

	_objectMgr->spawnObject(0x0000, Vector2(750, 700));

	//_objectMgr->spawnObject(0x0001, Vector2(800, 700));
	//_objectMgr->spawnObject(0x0001, Vector2(750, 700));
	_objectMgr->spawnObject(0x0001, Vector2(820, 700));
	//_objectMgr->spawnObject(0x0002, Vector2(300, 700));

	_img = IMAGE_MANAGER->findImage("Floor1Door");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, false);
	_ani->setFPS(15);
	_ani->start();



	_npcMgr->spawnNpc(NPC_TYPE::ENTRANCE, Vector2(570, 573), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(930, 620), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;
}

void StartRoom2::release()
{
	Stage::release();
}

void StartRoom2::update(float const elapsedTime)
{
	Stage::update(elapsedTime);

	_ani->frameUpdate(elapsedTime);
}

void StartRoom2::render()
{
	

	Stage::render();
}

