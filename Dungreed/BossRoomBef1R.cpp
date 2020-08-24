#include "BossRoomBef1R.h"

void BossRoomBef1R::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/BossRoomBef1.map");

	_respawnPosition[0] = Vector2(570, 670);

	_npcMgr->spawnNpc(NPC_TYPE::ENTRANCE, Vector2(570, 642), DIRECTION::LEFT);

	SOUND_MANAGER->stop("Floor1_BGM");
	SOUND_MANAGER->stop("BossRoomBef");
	SOUND_MANAGER->play("BossRoomBef", 1.0f);

	_torchImg = IMAGE_MANAGER->findImage("Torch");
	_torchAni = new Animation;
	_torchAni->init(_torchImg->getWidth(), _torchImg->getHeight(), _torchImg->getMaxFrameX(), _torchImg->getMaxFrameY());
	_torchAni->setDefPlayFrame(false, true);
	_torchAni->setFPS(15);
	_torchAni->start();
}

void BossRoomBef1R::release()
{
	Stage::release();
}

void BossRoomBef1R::update(float const elapsedTime)
{

	Stage::update(elapsedTime);
	_torchAni->frameUpdate(elapsedTime);
}

void BossRoomBef1R::render()
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
	_torchImg->aniRender(CAMERA->getRelativeV2(Vector2(300, 500)), Vector2(sizeX, sizeY), _torchAni);

	_torchImg->aniRender(CAMERA->getRelativeV2(Vector2(800, 500)), Vector2(sizeX, sizeY), _torchAni);
	_torchImg->aniRender(CAMERA->getRelativeV2(Vector2(1100, 500)), Vector2(sizeX, sizeY), _torchAni);

	_npcMgr->render();
	_enemyMgr->render();
	_objectMgr->render();
	_projectileMgr->render();
	
}
