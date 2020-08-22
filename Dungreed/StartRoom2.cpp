#include "StartRoom2.h"

void StartRoom2::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/StartRoom2_RB.map");

	
	_respawnPosition[0] = Vector2(565, 670);

	//_respawnPosition[2] = Vector2(1450, 670);
	
	_respawnPosition[3] = Vector2(1200, 670);

	/*makeDoor(Vector2(TILESIZE * 24 + TILESIZE * 0.5, TILESIZE * 9), DIRECTION::RIGHT);
	makeDoor(Vector2(TILESIZE * 19, TILESIZE * 14 + TILESIZE * 0.5), DIRECTION::DOWN);*/	

	_objectMgr->spawnObject(0x0000, Vector2(500, 700));

	_objectMgr->spawnObject(0x0001, Vector2(200, 700));
	_objectMgr->spawnObject(0x0001, Vector2(380, 700));
	_objectMgr->spawnObject(0x0001, Vector2(430, 700));
	_objectMgr->spawnObject(0x0002, Vector2(300, 700));

	_img = IMAGE_MANAGER->findImage("Floor1Door");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, false);
	_ani->setFPS(15);
	_ani->start();



	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(930, 620), DIRECTION::LEFT);
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

	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(Vector2(570, 573)), _ani);
}

vector<tagShowNpc> StartRoom2::getNpcInfos()
{
	vector<tagShowNpc> result = Stage::getNpcInfos();
	tagShowNpc start;
	start.icon = IMAGE_MANAGER->findImage("UI/MAP/ICON_START");
	start.type = NPC_TYPE::END;
	result.insert(result.begin(), start);
	return result;
}
