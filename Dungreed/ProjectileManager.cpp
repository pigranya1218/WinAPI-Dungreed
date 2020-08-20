#include "stdafx.h"
#include "ProjectileManager.h"
#include "Stage.h"
#include "EnemyManager.h"

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
	for (int i = 0; i < _projectiles.size();)
	{
		_projectiles[i]->update(elapsedTime);

		if (!_projectiles[i]->getActive())
		{
			_projectiles[i]->release();
			delete _projectiles[i];
			_projectiles.erase(_projectiles.begin() + i);
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

bool ProjectileManager::checkEnemyCollision(Projectile* projectile, bool isOnceCollision)
{
	return _enemyManager->isHit(projectile, isOnceCollision);
}

bool ProjectileManager::checkPlayerCollision(Projectile* projectile, bool isOnceCollision)
{
	return _stage->isHitPlayer(projectile, isOnceCollision);
}

Vector2 ProjectileManager::getEnemyPos(Vector2 pos)
{
	return _enemyManager->getEnemyPos(pos);
}
