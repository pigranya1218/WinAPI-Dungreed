#include "stdafx.h"
#include "Stage.h"
#include "EnemyManager.h"

void EnemyManager::init()
{
}

void EnemyManager::release()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->release();

		//SAFE_DELETE(_enemies[i]);
	}
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

void EnemyManager::spawnEnemy(ENEMY_TYPE enemyType, const Vector2& pos, DIRECTION direction)
{
	Enemy* enemy;

	switch (enemyType)
	{
		case ENEMY_TYPE::BANSHEE:
		{
			enemy = new Banshee;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);

			break;
		}
		case ENEMY_TYPE::BAT_BOMB:
		{
			break;
		}		
		case ENEMY_TYPE::BAT_RED:
		{
			enemy = new BatRed;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);

			break;
		}
		case ENEMY_TYPE::BAT_NORMAL:
		{
			break;
		}
		case ENEMY_TYPE::BAT_ICE:
		{
			break;
		}
		case ENEMY_TYPE::BAT_GIANT_RED:
		{
			break;
		}
		case ENEMY_TYPE::BAT_GIANT_NORMAL:
		{
			break;
		}
		case ENEMY_TYPE::GHOST:
		{
			break;
		}
		case ENEMY_TYPE::LILITH:
		{
			break;
		}
		case ENEMY_TYPE::SKEL_BIG_NORMAL:
		{
			break;
		}
		case ENEMY_TYPE::SKEL_BIG_ICE:
		{
			break;
		}
		case ENEMY_TYPE::SKEL_DOG:
		{
			break;
		}
		case ENEMY_TYPE::SKEL_MAGICIAN_ICE:
		{
			break;
		}
	}

	_enemies.push_back(enemy);
}

void EnemyManager::moveEnemy(GameObject* object, const Vector2 moveDir)
{
	_stage->moveTo(object, moveDir);
}

Vector2 EnemyManager::getPlayerPos()
{
	return _stage->getPlayerPos();
}
