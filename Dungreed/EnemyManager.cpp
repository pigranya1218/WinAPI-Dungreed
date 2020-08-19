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
	for (int i = 0; i < _enemies.size();)
	{
		_enemies[i]->update(timeElapsed);

		if (!_enemies[i]->getActive())
		{
			_enemies[i]->dieEffect();	// Á×´Â ÀÌÆåÆ® Àç»ý

			_enemies[i]->release();
			SAFE_DELETE(_enemies[i]);
			_enemies.erase(_enemies.begin() + i);
		}
		else
		{
			++i;
		}
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
			enemy = new BatBomb;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
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
			enemy = new BatGiantNormal;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
		}
		break;
		case ENEMY_TYPE::GHOST:
		{
			enemy = new Ghost;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
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
			enemy = new SkelDog;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
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
			enemy = new SkelSmallDagger;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
		}
		break;
		case ENEMY_TYPE::SKEL_SMALL_GSWORD:
		{
			enemy = new SkelSmallGsword;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
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
			enemy = new Ovibos;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
		}
		break;
		case ENEMY_TYPE::NIFLHEIM:
		{
			enemy = new Niflheim;
			enemy->init(pos, direction);
			enemy->setEnemyManager(this);
		}
		break;
		case ENEMY_TYPE::BELIAL:
		{
			enemy = new Belial;
			enemy->init(pos);
			enemy->setEnemyManager(this);
		}
		break;
	}

	_enemies.push_back(enemy);
}

void EnemyManager::moveEnemy(GameObject* object, const Vector2 moveDir, bool collisionGround, bool collisionPlatForm)
{
	_stage->moveTo(object, moveDir, collisionGround, collisionPlatForm);
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

void EnemyManager::fireEnemy(Projectile * projectile, AttackInfo * attackInfo)
{
	return _stage->attack(projectile, attackInfo);
}

Vector2 EnemyManager::getPlayerPos()
{
	return _stage->getPlayerPos();
}

bool EnemyManager::isHit(FloatRect* rc, AttackInfo* info)
{
	bool result = false;
	for (int i = 0; i < _enemies.size(); i++)
	{
		if (_enemies[i]->isHit(rc, info))
		{
			result = _enemies[i]->hitEffect(rc, info);
		}
	}
	return result;
}

bool EnemyManager::isHit(FloatCircle* circle, AttackInfo* info)
{
	bool result = false;
	for (int i = 0; i < _enemies.size(); i++)
	{
		if (_enemies[i]->isHit(circle, info))
		{
			result = _enemies[i]->hitEffect(circle, info);
		}
	}
	return result;
}

bool EnemyManager::isHit(Projectile* projectile, bool isOnceCollision)
{
	bool result = false;
	for (int i = 0; i < _enemies.size(); i++)
	{
		if (_enemies[i]->isHit(projectile))
		{
			result = _enemies[i]->hitEffect(projectile);
			if (result && isOnceCollision)
			{
				return result;
			}
		}
	}
	return result;
}

void EnemyManager::showDamage(DamageInfo info, Vector2 pos)
{
	_stage->showDamage(info, pos);
}

void EnemyManager::showEnemyHp(float maxHp, float curHp, Vector2 pos)
{
	_stage->showEnemyHp(maxHp, curHp, pos);
}
