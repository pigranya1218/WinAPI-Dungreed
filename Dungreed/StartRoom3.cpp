#include "StartRoom3.h"

void StartRoom3::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/StartRoom3_B.map");

	
	_respawnPosition[0] = Vector2(620, 300);
	//_respawnPosition[3] = Vector2(620, 800);

	_objectMgr->spawnObject(0x0000, Vector2(400, 300));

	_objectMgr->spawnObject(0x0001, Vector2(200, 600));
	_objectMgr->spawnObject(0x0001, Vector2(280, 600));
	

	_objectMgr->spawnObject(0x0002, Vector2(600, 300));

	_img = IMAGE_MANAGER->findImage("Floor1Door");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, false);
	_ani->setFPS(15);
	_ani->start();

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(950, 700), DIRECTION::LEFT);
}

void StartRoom3::release()
{
	Stage::release();
}

void StartRoom3::update(float const elapsedTime)
{
	Stage::update(elapsedTime);

	_ani->frameUpdate(elapsedTime);
}

void StartRoom3::render()
{
	Stage::render();

	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(Vector2(640, 320)), _ani);
}


vector<tagShowNpc> StartRoom3::getNpcInfos()
{
	vector<tagShowNpc> result = Stage::getNpcInfos();
	tagShowNpc start;
	start.icon = IMAGE_MANAGER->findImage("UI/MAP/ICON_START");
	start.type = NPC_TYPE::END;
	result.insert(result.begin(), start);
	return result;
}
