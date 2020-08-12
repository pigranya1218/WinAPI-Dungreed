#include "stdafx.h"
#include "ProjectileManager.h"

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

void ProjectileManager::fire()
{
	for (int i = 0; i < _projectiles.size(); i++)
	{
		_projectiles[i]->fire();
	}
}
