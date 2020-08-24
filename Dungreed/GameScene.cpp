#include "stdafx.h"
#include "GameScene.h"
#include "RoomToRoomEvent.h"
#include "TimeRatioEvent.h"

HRESULT GameScene::init()
{
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

	vector<bool> isProcessed(static_cast<int>(GAME_EVENT_TYPE::END), false);


	// 배속 관리
	float originTime = TIME_MANAGER->getElapsedTime();
	if (originTime > 0.03)
	{
		originTime = 0.03;
	}
	float elapsedTime = originTime * _timeSpeed;
	
	for (int i = 0; i < _events.size();)
	{
		if (_events[i]->getRemainTime() <= 0)
		{
			_events.erase(_events.begin() + i);
		}
		else
		{
			if (_events[i]->getType() == GAME_EVENT_TYPE::TIME_RATIO)
			{
				isProcessed[static_cast<int>(GAME_EVENT_TYPE::TIME_RATIO)] = true;
				_events[i]->processEvent(elapsedTime);
				break;
			}
			i++;
		}
	}

	_player->update(elapsedTime);
	_stageMgr->update(elapsedTime);
	EFFECT_MANAGER->update(elapsedTime);
	CAMERA->processEvent(elapsedTime);
	_uiMgr->update(elapsedTime);

	for (int i = 0; i < _events.size();)
	{
		if (_events[i]->getRemainTime() <= 0)
		{
			_events.erase(_events.begin() + i);
		}
		else
		{
			if (isProcessed[static_cast<int>(_events[i]->getType())])
			{
				i++;
				continue;
			}
			isProcessed[static_cast<int>(_events[i]->getType())] = true;
			_events[i]->processEvent(elapsedTime);
			i++;
		}
	}
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

	vector<bool> isProcessed(static_cast<int>(GAME_EVENT_TYPE::END), false);
	for (int i = 0; i < _events.size(); i++)
	{
		if (isProcessed[static_cast<int>(_events[i]->getType())]) continue;
		isProcessed[static_cast<int>(_events[i]->getType())] = true;
		_events[i]->render();
	}

	CAMERA->render();
}


// 저장 정보를 가지고 게임을 세팅
void GameScene::loadInfo(tagLoadInfo const info)
{
	
}

Vector2 GameScene::getEnemyPos(Vector2 pos)
{
	return _stageMgr->getEnemyPos(pos);
}

vector<FloatRect> GameScene::getEnemyRects()
{
	return _stageMgr->getEnemyRects();
}

void GameScene::showDropItem(Item* item)
{
	_uiMgr->showDropItem(item);
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

void GameScene::pushR2REvent(COLORREF color, float remainTime)
{
	bool needMake = true;
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i]->getType() != GAME_EVENT_TYPE::R2R) continue;
		if (_events[i]->getRemainTime() < remainTime)
		{
			_events[i]->setRemainTime(remainTime);
			_events[i]->setTotalTime(remainTime);
			needMake = false;
			break;
		}
	}
	if (needMake)
	{
		RoomToRoomEvent* event = new RoomToRoomEvent;
		event->init(color, remainTime);
		_events.push_back(event);
	}
}

void GameScene::pushTimeRatioEvent(float ratio, float remainTime)
{
	TimeRatioEvent* event = new TimeRatioEvent;
	event->init(ratio, remainTime);
	_events.push_back(event);
}
