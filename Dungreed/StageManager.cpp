#include "stdafx.h"
#include "StageManager.h"
#include "Stage.h"
#include "GameScene.h"
#include "TestStage.h"

void StageManager::init()
{
	_currStageType = STAGE_TYPE::TEST;
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
	_currStage = new TestStage();
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
	return _gameScene->getPlayerPos();
}
