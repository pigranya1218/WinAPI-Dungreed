#include "stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init()
{
	_player = new Player;
	_player->init();
	_player->setGameScene(this);

	_stageMgr = new StageManager;
	_stageMgr->init();
	_stageMgr->setGameScene(this);

	_uiMgr = new UIManager;
	_uiMgr->init();
	_uiMgr->setGameScene(this);

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
	// 배속 관리
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
}


// 저장 정보를 가지고 게임을 세팅
void GameScene::loadInfo(tagLoadInfo const info)
{
	
}
