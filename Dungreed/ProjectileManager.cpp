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
}

void ProjectileManager::render()
{
	for (int i = 0; i < _projectiles.size(); i++)
	{
		_projectiles[i]->render();
	}
}

void ProjectileManager::moveTo(GameObject* gameObject, Vector2 moveDir)
{
	_stage->moveTo(gameObject, moveDir);
}
