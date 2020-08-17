#include "stdafx.h"
#include "ProjectileManager.h"
#include "Stage.h"

void ProjectileManager::init()
{
}

void ProjectileManager::release()
{
	for (int i = 0; i < _projectiles.size(); i++)
	{
		_projectiles[i]->release();
	}
}

void ProjectileManager::update(float const elapsedTime)
{
	for (int i = 0; i < _projectiles.size(); i++)
	{
		_projectiles[i]->update(elapsedTime);
	}
	for (int i = 0; i < _projectiles.size();)
	{
		if (!_projectiles[i]->getActive())
		{
			_projectiles[i]->release();
			delete _projectiles[i];
			_projectiles.erase(_projectiles.begin() + i);
			//break;
		}
		else
		{
			++i;
		}
	}
}

void ProjectileManager::render()
{
	for (int i = 0; i < _projectiles.size(); i++)
	{
		_projectiles[i]->render();
	}
}

void ProjectileManager::moveTo(GameObject* gameObject, Vector2 moveDir, bool checkCollisionGround, bool checkCollisionPlatform)
{
	_stage->moveTo(gameObject, moveDir, checkCollisionGround, checkCollisionPlatform);
}
