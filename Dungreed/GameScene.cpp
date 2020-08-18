#include "stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init()
{
	CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 0, 0);
	CAMERA->setLT(Vector2(0, 0));

	_timeSpeed = 1;
	_player = new Player;
	_player->init();
	_player->setGameScene(this);

	_stageMgr = new StageManager;
	_stageMgr->init();
	_stageMgr->setGameScene(this);
	_stageMgr->setPlayer(_player);

	_uiMgr = new UIManager;
	_uiMgr->init();
	_uiMgr->setGameScene(this);
	_uiMgr->setPlayer(_player);
	_uiMgr->setStageManager(_stageMgr);
	_stageMgr->setUIManager(_uiMgr);


	return S_OK;
}

void GameScene::release()
{
	_player->release();
	_stageMgr->release();
	_uiMgr->release();
}

void GameScene::update()
{
	if (KEY_MANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		if (!_uiMgr->isActive())
		{
			PostQuitMessage(0);
		}
	}

	// 배속 관리
	float elapsedTime = TIME_MANAGER->getElapsedTime() * _timeSpeed;
	
	_stageMgr->update(elapsedTime);
	_player->update(elapsedTime);
	EFFECT_MANAGER->update(elapsedTime);
	CAMERA->setXY(_player->getPosition());
	_uiMgr->update(elapsedTime);
}

void GameScene::render()
{
	_stageMgr->render();
	_player->render();
	EFFECT_MANAGER->render();

	_uiMgr->render();

	if (_uiMgr->isActive())
	{
		IMAGE_MANAGER->findImage("CURSOR_BASIC")->setScale(5);
		IMAGE_MANAGER->findImage("CURSOR_BASIC")->render(Vector2(_ptMouse.x, _ptMouse.y));
	}
	else
	{
		IMAGE_MANAGER->findImage("CURSOR_SHOOTING")->setScale(4);
		IMAGE_MANAGER->findImage("CURSOR_SHOOTING")->render(Vector2(_ptMouse.x, _ptMouse.y));
	}
	
}


// 저장 정보를 가지고 게임을 세팅
void GameScene::loadInfo(tagLoadInfo const info)
{
	
}

void GameScene::moveTo(GameObject * object, Vector2 moveDir)
{
	_stageMgr->moveTo(object, moveDir);
}

void GameScene::attack(FloatRect* rect, AttackInfo* info)
{
	_stageMgr->attack(rect, info);
}

void GameScene::attack(FloatCircle* circle, AttackInfo* info)
{
	_stageMgr->attack(circle, info);
}

void GameScene::attack(Projectile* projectile, AttackInfo* info)
{
	_stageMgr->attack(projectile, info);
}

bool GameScene::isUIActive()
{
	return _uiMgr->isActive();
}
