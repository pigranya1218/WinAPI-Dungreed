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

	_objectMgr->spawnObject(0x0000, Vector2(500, 700));
	_objectMgr->spawnObject(0x0001, Vector2(200, 700));
	_objectMgr->spawnObject(0x0001, Vector2(380, 700));
	_objectMgr->spawnObject(0x0001, Vector2(430, 700));
	_objectMgr->spawnObject(0x0002, Vector2(300, 700));


	_npcMgr->spawnNpc(NPC_TYPE::ENTRANCE, Vector2(570, 642), DIRECTION::LEFT);
	_npcMgr->spawnNpc(NPC_TYPE::GATE, Vector2(870, 600), DIRECTION::LEFT);

	_roomType = ROOMTYPE::NORMAL;

	_torchImg = IMAGE_MANAGER->findImage("Torch");
	_torchAni = new Animation;
	_torchAni->init(_torchImg->getWidth(), _torchImg->getHeight(), _torchImg->getMaxFrameX(), _torchImg->getMaxFrameY());
	_torchAni->setDefPlayFrame(false, true);
	_torchAni->setFPS(15);
	_torchAni->start();
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
	_torchAni->frameUpdate(elapsedTime);
}

void StartRoom1::render()
{
	D2D_RENDERER->fillRectangle(FloatRect(0, 0, TILESIZE * 30, TILESIZE * 20), 51, 49, 67, 1);
	for (int i = 0; i < _tile[0].tileX * _tile[0].tileY; ++i)
	{
		if (_tile[i].tileFrameX[0] != -1)
		{
			_tileImage->setScale(4);
			CAMERA->frameRender(_tileImage, _tile[i].rc.getCenter(), _tile[i].tileFrameX[0], _tile[i].tileFrameY[0]);
		}
		if (_tile[i].tileFrameX[1] != -1)
		{
			_tileImage->setScale(4);
			CAMERA->frameRender(_tileImage, _tile[i].rc.getCenter(), _tile[i].tileFrameX[1], _tile[i].tileFrameY[1]);
		}
	}

	int sizeX = _torchImg->getSize().x * 4;
	int sizeY = _torchImg->getSize().y * 4;
	_torchImg->aniRender(CAMERA->getRelativeV2(Vector2(400, 420)), Vector2(sizeX, sizeY), _torchAni);
	_torchImg->aniRender(CAMERA->getRelativeV2(Vector2(800, 420)), Vector2(sizeX, sizeY), _torchAni);

	_npcMgr->render();
	_enemyMgr->render();
	_objectMgr->render();
	_projectileMgr->render();
	
	
}
