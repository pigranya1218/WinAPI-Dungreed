#include "stdafx.h"
#include "EnemyManager.h"

void EnemyManager::init()
{
}

void EnemyManager::release()
{
}

void EnemyManager::update(float const timeElapsed)
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->update(timeElapsed);
	}
}

void EnemyManager::render()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->render();
	}
}
