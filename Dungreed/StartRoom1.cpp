#include "StartRoom1.h"
#include "StageManager.h"

void StartRoom1::init()
{
	
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/StartRoom1_R.map");
	//_direction.push_back(DIRECTION::RIGHT);
	
	// makeDoor(Vector2(TILESIZE * 19 + TILESIZE * 0.5, TILESIZE * 10), DIRECTION::RIGHT);
	_respawnPosition[0] = Vector2(570,670); // 맨 처음 초기화되는 위치
	// _respawnPosition[2] = Vector2(1130,670); // 오른쪽에서 들어올 때 위치

	_img = IMAGE_MANAGER->findImage("Floor1Door");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, false);
	_ani->setFPS(15);
	_ani->start();

	_objectMgr->spawnObject(0x0000, Vector2(500, 600));
	_objectMgr->spawnObject(0x0001, Vector2(200, 600));
	_objectMgr->spawnObject(0x0001, Vector2(380, 600));
	_objectMgr->spawnObject(0x0001, Vector2(430, 600));
	_objectMgr->spawnObject(0x0002, Vector2(300, 600));

	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(870, 400), DIRECTION::LEFT);


}

void StartRoom1::release()
{
	Stage::release();
}

void StartRoom1::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
	int stageWidth = _tile[0].tileX*TILESIZE;
	
	
	_ani->frameUpdate(elapsedTime);
}

void StartRoom1::render()
{
	Stage::render();

	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(Vector2(570, 642)), _ani);
}
