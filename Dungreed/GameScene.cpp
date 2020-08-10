#include "stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init()
{
	_timeSpeed = 1;
	_player = new Player;
	_player->init();
	_player->setGameScene(this);

	_stageMgr = new StageManager;
	_stageMgr->init();
	_stageMgr->setGameScene(this);

	_uiMgr = new UIManager;
	_uiMgr->init();
	_uiMgr->setGameScene(this);
	_uiMgr->setPlayer(_player);

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
		PostQuitMessage(0);
	}

	// ��� ����
	float elapsedTime = TIME_MANAGER->getElapsedTime() * _timeSpeed;
	
	_player->update(elapsedTime);
	_stageMgr->update(elapsedTime);
	EFFECT_MANAGER->update(elapsedTime);

	_uiMgr->update(elapsedTime);
}

void GameScene::render()
{
	_player->render();
	_stageMgr->render();
	EFFECT_MANAGER->render();

	_uiMgr->render();

	IMAGE_MANAGER->findImage("CURSOR_SHOOTING")->setScale(4);
	IMAGE_MANAGER->findImage("CURSOR_SHOOTING")->render(Vector2(_ptMouse.x, _ptMouse.y));
}


// ���� ������ ������ ������ ����
void GameScene::loadInfo(tagLoadInfo const info)
{
	
}

void GameScene::moveTo(GameObject * object, Vector2 moveDir)
{
	_stageMgr->moveTo(object, moveDir);
}
