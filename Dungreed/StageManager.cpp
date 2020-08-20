#include "stdafx.h"
#include "StageManager.h"
#include "GameScene.h"
#include "Player.h"
#include "UIManager.h"

#include "DebugStage.h"
#include "VillageStage.h"

#include "AllRoom.h"


void StageManager::init()
{
	_currStageType = STAGE_TYPE::TEST;
	//_currStageType = STAGE_TYPE::VILLAGE;
	
	makeStage();

	_roomIndex = 0;


	rnd = RANDOM->getFromIntTo(0, 5);
	k = RANDOM->getFromIntTo(4, 6);
	l = RANDOM->getFromIntTo(4, 6);
	_currIndexX = k;
	_currIndexY = l;
	makeNum = 0;
}

void StageManager::release()
{
	
	releaseStage();
}

void StageManager::update(float const elapsedTime)
{
	if (_currStageType == STAGE_TYPE::DUNGEON_NORMAL)
	{
		/*if (_roomIndex >= _stages.size())return;
			
		_stages[_roomIndex]->update(elapsedTime);*/
		_vStage[_currIndexX][_currIndexY]->update(elapsedTime);

	}

	else	_currStage->update(elapsedTime);
}

void StageManager::render()
{
	if (_currStageType == STAGE_TYPE::DUNGEON_NORMAL)
	{
		/*if (_roomIndex >= _stages.size())return;
		_stages[_roomIndex]->render();*/
		_vStage[_currIndexX][_currIndexY]->render();
	}
	else _currStage->render();
}

void StageManager::attack(FloatRect* rect, AttackInfo* info)
{
	if (info->team == OBJECT_TEAM::PLAYER)
	{
		_currStage->isHitEnemy(rect, info);
	}
	else
	{
		if (_player->isHit(rect, info))
		{
			_player->hitEffect(rect, info);
		}
	}
}

void StageManager::attack(FloatCircle* circle, AttackInfo* info)
{
	if (info->team == OBJECT_TEAM::PLAYER)
	{
		_currStage->isHitEnemy(circle, info);
	}
	else
	{
		if (_player->isHit(circle, info))
		{
			_player->hitEffect(circle, info);
		}
	}
}

void StageManager::attack(Projectile* projectile, AttackInfo* info)
{
	_currStage->attack(projectile, info);
}


void StageManager::moveTo(GameObject* object, Vector2 moveDir)
{
	if (_currStageType == STAGE_TYPE::DUNGEON_NORMAL)
	{
		/*if (_roomIndex >= _stages.size())return;
		_stages[_roomIndex]->moveTo(object, moveDir);*/
		_vStage[_currIndexX][_currIndexY]->moveTo(object, moveDir);
	}
	else _currStage->moveTo(object, moveDir);


	
}

void StageManager::nextStage()
{
	_currStageType = static_cast<STAGE_TYPE>(static_cast<int>(_currStageType) + 1);
	releaseStage();
	makeStage();
}

void StageManager::moveRoom()
{
	_currIndexX += 1;
	
	_vStage[_currIndexX][_currIndexY]->setStageManager(this);
	_vStage[_currIndexX][_currIndexY]->init();


	//_currIndexY += 1;
	//_roomIndex += 1;
}

void StageManager::makeStage()
{
	ZeroMemory(&_stage, sizeof(_stage));
	ZeroMemory(&_vStage, sizeof(_vStage));
	SAFE_DELETE(_stage)
	
	_vStage.resize(10);
	vector<vector<bool>> isMadeStage (10, vector<bool>(10, false));
	for (int i = 0; i < 10; i++)
	{
		_vStage[i].resize(10);
	}
	vector<bool> specialStage (3, false);

	switch (_currStageType)
	{
	case STAGE_TYPE::VILLAGE:
		_currStage = new VillageStage();
		_currStage->setStageManager(this);
		_currStage->init();
		break;
	case STAGE_TYPE::DUNGEON_NORMAL:
		_currStage = new StartRoom1();
		_currStage->setStageManager(this);
		_currStage->init();
		
	//case STAGE_TYPE::VILLAGE:
	//	_currStage = new VillageStage();
	//	_currStage->setStageManager(this);
	//	_currStage->init();
	//	break;
	//case STAGE_TYPE::DUNGEON_NORMAL:
	//	_currStage = new StartRoom1();
	//	_currStage->setStageManager(this);
	//	_currStage->init();

	//	int indexX = RANDOM->getFromIntTo(4,6);
	//	int indexY = RANDOM->getFromIntTo(4, 6);

		//int indexX = RANDOM->getFromIntTo(4,6);
		//int indexY = RANDOM->getFromIntTo(4, 6);
	//	_vStage[indexX][indexY] = _currStage;
	//	_vStage[indexX][indexY]->setStageManager(this);
	//	_vStage[indexX][indexY]->init();

		_vStage[k][l] = _currStage;
		for (int i = 0; i < _vStage.size(); i++)
		{
			makeRoom(k+i, l+i);
		}
		/*makeRoom(k, l);
		makeRoom(k+1, l+1);*/

		_vStage[_currIndexX][_currIndexY]->setStageManager(this);
		_vStage[_currIndexX][_currIndexY]->init();
		//_vStage[k][l]->setIsMade(true);

		//makeRoom(indexX, indexY, specialStage, isMadeStage);
		
		break;
	case STAGE_TYPE::DUNGEON_BOSS:
		break;
	//	makeRoom(indexX, indexY, specialStage, isMadeStage);
	//	break;
	//case STAGE_TYPE::DUNGEON_BOSS:
	//	break;
	case STAGE_TYPE::TEST:
		_currStage = new DebugStage();
		_currStage->setStageManager(this);
		_currStage->setUIManager(_uiMgr);
		_currStage->setPlayer(_player);
		_currStage->init();
		break;
	default:
		break;
	}
}

void StageManager::releaseStage()
{
	for (int i = 0; i < _stages.size(); i++)
	{
		_stages[i]->release();
		delete _stages[i];
	}
}

Vector2 StageManager::getPlayerPos()
{
	return _player->getPosition();
}

void StageManager::setPlayerPos( int x, int y)
{
	
	_player->setPosition(Vector2(x, y));
}

void StageManager::makeRoom(int x1, int y1)
{
	
	if (makeNum > 5)return;
	makeNum++;


	//if (_vStage[x1][y1]->getOpenDirection(0))
	//{
	//	//if (_vStage[x1 - 1][y1]->getIsMade())return;
	//	Stage* newStage;
	//	if (rnd == 0)_stage2 = new Room20LTRB();
	//	else if (rnd == 1)_stage2 = new Room2LTR();
	//	else if (rnd == 2)_stage2 = new Room4LR();
	//	else if (rnd == 3)_stage2 = new Room21LR();
	//	else if (rnd == 4)_stage2 = new Room22LTRB();
	//	else _stage2 = new Room20LTRB();
	//	_stage2->setStageManager(this);
	//	_stage2->init();
	//	//_stage2->setIsMade(true);

	//	int makeIndexX=x1-1;
	//	int makeIndexY=y1;
	//	_vStage[makeIndexX][makeIndexY] = _stage2;
	//	//_currStage = _stage;
	//	makeRoom(makeIndexX, makeIndexY);

	//}
	//if (_vStage[x1][y1]->getOpenDirection(1))
	//{
	//	//if (_vStage[x1][y1-1]->getIsMade())return;
	//	if (rnd == 0)_stage2 = new Room20LTRB;
	//	else if (rnd == 1)_stage2 = new Room22LTRB;
	//	else if (rnd == 2)_stage2 = new Room2LTR;
	//	else _stage2 = new Room20LTRB;
	//	_stage2->setStageManager(this);
	//	_stage2->init();
	//	//_stage2->setIsMade(true);

	//	int makeIndexX = x1 ;
	//	int makeIndexY = y1-1;
	//	_vStage[makeIndexX][makeIndexY] = _stage2;
	//	//_currStage = _stage;
	//}
	
		//if (_vStage[x1+1][y1]->getIsMade())return;
		if (_currIndexX + 1 == 9)
		{
			_stage = new Room8L;
			_stage2->setStageManager(this);
			_stage2->init();
			//_stage2->setIsMade(true);
		}
		else
		{
			if (rnd == 0)_stage2 = new Room20LTRB();
			else if (rnd == 1)_stage2 = new Room2LTR();
			else if (rnd == 2)_stage2 = new Room4LR();
			else if (rnd == 3)_stage2 = new Room21LR();
			else if (rnd == 4)_stage2 = new Room22LTRB();
			else _stage2 = new Room20LTRB();
			_stage2->setStageManager(this);
			_stage2->init();
			//_stage2->setIsMade(true);
		}
		int makeIndexX = x1 + 1;
		int makeIndexY=y1;
		_vStage[x1 + 1][y1] = _stage2;

		//makeRoom(makeIndexX, makeIndexY);
		//_currStage = _stage;
		
	

	//if (_vStage[x1][y1]->getOpenDirection(3))
	//{
	//	//if (_vStage[x1][y1+1]->getIsMade())return;
	//	if (rnd == 0)_stage2 = new Room20LTRB;
	//	else if (rnd == 1)_stage2 = new Room22LTRB;
	//	else if (rnd == 2)_stage2 = new Room2LTR;
	//	else _stage2 = new Room20LTRB;
	//	_stage2->setStageManager(this);
	//	_stage2->init();
	//	//_stage2->setIsMade(true);
	//	int makeIndexX = x1;
	//	int makeIndexY = y1+1;
	//	_vStage[makeIndexX][makeIndexY] = _stage2;

	if (_vStage[x1][y1]->getOpenDirection(3))
	{
		if (rnd == 0)_stage2 = new Room20LTRB;
		else if (rnd == 1)_stage2 = new Room22LTRB;
		else if (rnd == 2)_stage2 = new Room2LTR;
		else _stage2 = new Room20LTRB;
		_stage2->setStageManager(this);
		_stage2->init();
		int makeIndexX = x1;
		int makeIndexY = y1+1;
		_vStage[makeIndexX][makeIndexY] = _stage2;
		//_currStage = _stage;
	}
}

void StageManager::showDamage(DamageInfo info, Vector2 pos)
{
	_uiMgr->showDamage(info, pos);
}

void StageManager::showEnemyHp(float maxHp, float curHp, Vector2 pos)
{
	_uiMgr->showEnemyHp(maxHp, curHp, pos);
	//	makeRoom(makeIndexX, makeIndexY);
	//	//_currStage = _stage;
	//}
}


