#include "stdafx.h"
#include "StageManager.h"
#include "GameScene.h"
#include "Player.h"

#include "DebugStage.h"
#include "VillageStage.h"

#include "AllRoom.h"


void StageManager::init()
{
	//_currStageType = STAGE_TYPE::TEST;
	_currStageType = STAGE_TYPE::VILLAGE;
	
	makeStage();

	_roomIndex = 0;
}

void StageManager::release()
{
	releaseStage();
}

void StageManager::update(float const elapsedTime)
{
	if (_currStageType == STAGE_TYPE::DUNGEON_NORMAL)
	{
		if (_roomIndex >= _stages.size())return;
			
		_stages[_roomIndex]->update(elapsedTime);
		
	}

	else	_currStage->update(elapsedTime);
}

void StageManager::render()
{
	if (_currStageType == STAGE_TYPE::DUNGEON_NORMAL)
	{
		if (_roomIndex >= _stages.size())return;
		_stages[_roomIndex]->render();
		
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
		_player->isHit(rect, info);
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
		_player->isHit(circle, info);
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
		if (_roomIndex >= _stages.size())return;
		_stages[_roomIndex]->moveTo(object, moveDir);

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
	_roomIndex += 1;
}

void StageManager::makeStage()
{
	switch (_currStageType)
	{
	case STAGE_TYPE::VILLAGE:
		_currStage = new VillageStage();
		_currStage->setStageManager(this);
		_currStage->init();
		break;
	case STAGE_TYPE::DUNGEON_NORMAL:

		_currStage = new StartRoom1();
		_stages.push_back(_currStage);

		_currStage = new Room1();
		_stages.push_back(_currStage);

		_currStage = new Room2();
		_stages.push_back(_currStage);

		_currStage = new RestaurantRoom();
		_stages.push_back(_currStage);

		_currStage = new DungeonShopRoom();
		_stages.push_back(_currStage);
		
		_stages[_roomIndex]->setStageManager(this);
		_stages[_roomIndex]->init();

		break;
	case STAGE_TYPE::DUNGEON_BOSS:
		break;
	case STAGE_TYPE::TEST:
		_currStage = new DebugStage();
		_currStage->setStageManager(this);
		_currStage->init();
		break;
	default:
		break;
	}

	
	
	//_currStage = new RestaurantRoom();
	
	

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


