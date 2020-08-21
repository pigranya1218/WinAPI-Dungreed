#include "stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init()
{
	CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, 0, 0);
	CAMERA->setLT(Vector2(0, 0));

	_timeSpeed = 1;
	
	_player = new Player;
	_player->setGameScene(this);
	_player->init();

	_uiMgr = new UIManager;
	_uiMgr->setPlayer(_player);
	_uiMgr->setGameScene(this);
	_uiMgr->init();
	
	_stageMgr = new StageManager;
	_stageMgr->setUIManager(_uiMgr);
	_stageMgr->setPlayer(_player);
	_stageMgr->setGameScene(this);
	_stageMgr->init();

	_uiMgr->setStageManager(_stageMgr);


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
	
	_player->update(elapsedTime);
	_stageMgr->update(elapsedTime);
	EFFECT_MANAGER->update(elapsedTime);
	CAMERA->processEvent(elapsedTime);
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

Vector2 GameScene::getEnemyPos(Vector2 pos)
{
	return _stageMgr->getEnemyPos(pos);
}

void GameScene::moveTo(GameObject * object, Vector2 moveDir)
{
	_stageMgr->moveTo(object, moveDir);
}

void GameScene::moveRoom(Vector2 dir)
{
	_stageMgr->moveRoom(dir);
}

bool GameScene::attack(FloatRect* rect, AttackInfo* info)
{
	return _stageMgr->attack(rect, info);
}

bool GameScene::attack(FloatCircle* circle, AttackInfo* info)
{
	return _stageMgr->attack(circle, info);
}

void GameScene::attack(Projectile* projectile, AttackInfo* info)
{
	_stageMgr->attack(projectile, info);
}

bool GameScene::isUIActive()
{
	return _uiMgr->isActive();
}

void GameScene::showDamage(DamageInfo info, Vector2 pos)
{
	_uiMgr->showDamage(info, pos);
}
