#include "stdafx.h"
#include "EnemyManager.h"
#include "TestScene.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::init()
{
	return S_OK;
}

void EnemyManager::release()
{
	_vEnemy.clear();
}

void EnemyManager::update()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->update();
	}
}

void EnemyManager::render()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->render();
	}

	
}

void EnemyManager::spawn(const Vector2& pos, ENEMY_TYPE enemyType, DIRECTION direction)
{
	Enemy* enemy;
	switch (enemyType)
	{
		case ENEMY_TYPE::BANSHEE: 
		{
			enemy = new Banshee;
			enemy->init(pos, direction);
			break;
		}			
		case ENEMY_TYPE::BAT_BOMB:
		break;
		case ENEMY_TYPE::BAT_RED:
		{
			enemy = new BatRed;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
			break;
		}
		
	case ENEMY_TYPE::BAT_NORMAL:
		break;
		case ENEMY_TYPE::BAT_ICE:
		{

		}
		break;
	case ENEMY_TYPE::BAT_GIANT_RED:
		break;
	case ENEMY_TYPE::BAT_GIANT_NORMAL:
		break;
	case ENEMY_TYPE::GHOST:
		break;
	case ENEMY_TYPE::LILITH:
		break;
	case ENEMY_TYPE::SKEL_BIG_NORMAL:
		break;
		case ENEMY_TYPE::SKEL_BIG_ICE:
		{
			enemy = new SkelBigIce;
			enemy->init(pos, direction);
			break;
		}
		
	case ENEMY_TYPE::SKEL_DOG:
		break;
	case ENEMY_TYPE::SKEL_MAGICIAN_ICE:
		break;
	default:
		break;
	}
	
	_vEnemy.push_back(enemy);
}

void EnemyManager::moveEnemy(GameObject * gObject, Vector2& pos)
{
	_scene->moveGameObject(gObject, pos);
}
