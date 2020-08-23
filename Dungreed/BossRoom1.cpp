#include "stdafx.h"
#include "BossRoom1.h"
#include "StageManager.h"
#include "UIManager.h"

void BossRoom1::startEventScene()
{
	_isEventScene = true;
	_timeCount = 4;
	Vector2 spawnPos(WINSIZEX / 2, WINSIZEY / 2 + 300);
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BELIAL, spawnPos);
	Vector2 cameraPos = spawnPos;
	cameraPos.y += 140;
	CAMERA->pushMoveEvnet(cameraPos, 2.5, 1.5);
	
	vector<FloatRect> fillRect;
	fillRect.push_back(FloatRect(0, 0, WINSIZEX, 150));
	fillRect.push_back(FloatRect(0, WINSIZEY - 150, WINSIZEX, WINSIZEY));
	CAMERA->pushFillEvnet(fillRect, 1, 1, 1, 1, RGB(0, 0, 0));
}

void BossRoom1::init()
{
	Stage::init();
	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	loadMap("room/BossRoom.map");
}

void BossRoom1::release()
{
	Stage::release();
}

void BossRoom1::update(float const elapsedTime)
{
	_projectileMgr->update(elapsedTime);
	_objectMgr->update(elapsedTime);
	_npcMgr->update(elapsedTime);
	_enemyMgr->update(elapsedTime);

	int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;
	Vector2 playerPos = _stageManager->getPlayerPos();

	if (!_isEventScene)
	{
		CAMERA->setXY(Vector2(round(playerPos.x), round(playerPos.y)));
	}

	switch (_state)
	{
	case STAGE_STATE::IDLE:
	{
		if (playerPos.x >= stageWidth / 2)
		{
			_state = STAGE_STATE::START;
			startEventScene();
		}
	}
	break;
	case STAGE_STATE::START:
	{
		for (int i = 0; i < 4; i++)
		{
			if (_doors[i] != nullptr)
			{
				_doors[i]->setOpen(false);
			}
		}
		
		if (_timeCount > 0)
		{
			_timeCount = max(0, _timeCount - elapsedTime);
			if (_timeCount == 0)
			{
				_isEventScene = false;
			}
		}
		else
		{
			if (!_uiManager->getBossHpActive())
			{
				_state = STAGE_STATE::FINISH;
			}
		}
	}
	break;
	case STAGE_STATE::FINISH:
	{
		for (int i = 0; i < 4; i++)
		{
			if (_doors[i] != nullptr)
			{
				_doors[i]->setOpen(true);
			}
		}
	}
	break;
	}

	if (KEY_MANAGER->isOnceKeyDown('L'))
	{
		for (int i = 0; i < 4; i++)
		{
			if (_doors[i] != nullptr)
			{
				_doors[i]->setOpen(!_doors[i]->isOpen());
			}
		}
	}
}

void BossRoom1::render()
{
	Stage::render();

	if (_isEventScene)
	{
		float infoTime = 1;
		if (4 - infoTime >= _timeCount)
		{
			float alpha = 1;
			if (4 - infoTime - 1 >= _timeCount)
			{
				alpha = min(alpha, _timeCount / (4 - infoTime - 2));
			}
			else
			{
				alpha = min(alpha, (1 - (_timeCount - 2)));
			}
			D2D_RENDERER->renderTextField(20, 670, L"벨리알", RGB(255, 255, 255), 55, 300, 50, alpha);
			D2D_RENDERER->renderTextField(35, 615, L"감옥의 수문장", RGB(255, 255, 255), 45, 300, 40, alpha);
		}
	}
}
