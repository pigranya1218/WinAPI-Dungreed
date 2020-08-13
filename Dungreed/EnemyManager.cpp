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
		}
		break;
		case ENEMY_TYPE::BAT_BOMB:
		{
		}		
		break;
		case ENEMY_TYPE::BAT_RED:
		{
			enemy = new BatRed;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
		}
		break;
		case ENEMY_TYPE::BAT_NORMAL:
		{
			enemy = new BatNormal;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
		}
		break;
		case ENEMY_TYPE::BAT_ICE:
		{
			enemy = new BatIce;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
		}
		break;
		case ENEMY_TYPE::BAT_GIANT_RED:
		{
			enemy = new BatGiantRed;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
		}
		break;
		case ENEMY_TYPE::BAT_GIANT_NORMAL:
		{
		}
		break;
		case ENEMY_TYPE::GHOST:
		{
		}
		break;
		case ENEMY_TYPE::LILITH:
		{
		}
		break;
		case ENEMY_TYPE::SKEL_BIG_NORMAL:
		{
			enemy = new SkelBigNormal;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
		}
		break;
		case ENEMY_TYPE::SKEL_BIG_ICE:
		{
			enemy = new SkelBigIce;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
		}
		break;
		case ENEMY_TYPE::SKEL_DOG:
		{
		}
		break;
		case ENEMY_TYPE::SKEL_MAGICIAN_ICE:
		{
			enemy = new SkelMagicianIce;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
		}
		break;
		case ENEMY_TYPE::SKEL_SMALL_BOW:
		{
			enemy = new SkelSmallBow;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
		}
		break;
		case ENEMY_TYPE::SKEL_SMALL_DAGGER:
		{

		}
		break;
		case ENEMY_TYPE::SKEL_SMALL_GSWORD:
		{

		}
		break;
		case ENEMY_TYPE::MINOTAURS:
		{
			enemy = new Minotaurs;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
		}
		break;
		case ENEMY_TYPE::OVIBOS:
		{

		}
	}

	_enemies.push_back(enemy);
}

void EnemyManager::moveEnemy(GameObject* object, const Vector2 moveDir)
{
	_stage->moveTo(object, moveDir);
}

bool EnemyManager::detectPlayer(GameObject* object, const float distance)
{
	const Vector2 playerPos = _stage->getPlayerPos();
	const Vector2 enemyPos = object->getPosition();

	if (getDistance(playerPos.x, playerPos.y, enemyPos.x, enemyPos.y) < distance)
	{
		return true;
	}
	return false;

	
}

//void EnemyManager::fireEnemy()
//{
//	
//}

Vector2 EnemyManager::getPlayerPos()
{
	return _stage->getPlayerPos();
}