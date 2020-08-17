#include "stdafx.h"
#include "StageManager.h"
#include "GameScene.h"
#include "Player.h"

#include "DebugStage.h"
#include "VillageStage.h"
#include "RestaurantRoom.h"

void StageManager::init()
{
	_currStageType = STAGE_TYPE::TEST;
	//_currStageType = STAGE_TYPE::VILLAGE;
	
	makeStage();
}

void StageManager::release()
{
	releaseStage();
}

void StageManager::update(float const elapsedTime)
{
	_currStage->update(elapsedTime);
}

void StageManager::render()
{
	_currStage->render();
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
	_currStage->moveTo(object, moveDir);
}

void StageManager::nextStage()
{
	_currStageType = static_cast<STAGE_TYPE>(static_cast<int>(_currStageType) + 1);
	releaseStage();
	makeStage();
}

void StageManager::makeStage()
{
	_currStage = new DebugStage();
	//_currStage = new VillageStage();
	//_currStage = new RestaurantRoom();
	_currStage->setStageManager(this);
	_currStage->init();

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
