#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"

void Enemy::tagShootingInfo::fireBullet(EnemyManager * enemyManager, int fireCount)
{
	if (bullets.empty()) return;

	int fireLoop = (fireCount == 0) ? (bullets.size()) : (fireCount);

	// 생성해놓은 총알을
	for (int i = 0; i < fireLoop; i++)
	{
		// 발사한다.
		if (!bullets.empty())
		{
			AttackInfo* attackInfo = new AttackInfo;			
			attackInfo->minDamage = minDamage;
			attackInfo->maxDamage = maxDamage;
			attackInfo->trueDamage = trueDamage;
			attackInfo->knockBack = knockBack;
			attackInfo->team = OBJECT_TEAM::ENEMY;

			enemyManager->fireEnemy(bullets[bullets.size() - 1], attackInfo);
			//delete attackInfo;
			//bullets[bullets.size() - 1]->release();
			bullets.pop_back();
		}		
	}	
}

void Enemy::dieEffect()
{
	if (_state == ENEMY_STATE::DIE)
	{
		Vector2 drawSize = _img->getFrameSize() * _scale;
		drawSize.x = max(drawSize.x, drawSize.y);
		drawSize.y = max(drawSize.x, drawSize.y);
		EFFECT_MANAGER->play("Enemy_Destroy", _position, drawSize);
	}	
}

bool Enemy::isHit(FloatRect* rc, AttackInfo* info)
{
	// 2가지 검사를 함
	// 1. 이미 피격 처리를 한 공격인지에 대해 검사
	// 2. 공격 렉트와 Enemy 렉트의 충돌 여부

	// [1] 이미 피격 처리를 한 공격인지에 대해 검사
	bool alreadyAttacked = false;
	for (int i = 0; i < _attackedId.size(); i++)
	{
		if (_attackedId[i] == info->attackID)
		{
			alreadyAttacked = true;
			break;
		}
	}
	if (alreadyAttacked) return false; // 이미 피격처리한 공격이라면 피격 처리 안함

	// [2] 피격 판정이 이루어져야하는지 검사
	FloatRect enemyRc = FloatRect(_position, _size, PIVOT::CENTER);
	FloatRect attackRc = FloatRect(rc->getCenter(), rc->getSize(), PIVOT::CENTER);

	if (!FloatRect::intersect(enemyRc, attackRc)) // 사각형과 사각형의 충돌 검사 함수
	{
		return false; // 피격 판정이 아니므로 피격 처리 안함
	}

	if (_attackedId.size() == 10) // 피격 처리를 해야 하는데 공격 ID 저장 벡터 사이즈가 10이라면
	{
		_attackedId.erase(_attackedId.begin()); // 맨 먼저 들어온 ID를 제거하고
		_attackedId.push_back(info->attackID); // 맨 뒤에 새로운 공격 ID 추가
	}

	return true; // 위 검사 결과 피격 처리가 되어야 함
}

bool Enemy::isHit(FloatCircle* circle, AttackInfo* info)
{
	// 2가지 검사를 함
	// 1. 이미 피격 처리를 한 공격인지에 대해 검사
	// 2. 공격 호과 Enemy 렉트의 충돌 여부

	// [1] 이미 피격 처리를 한 공격인지에 대해 검사
	bool alreadyAttacked = false;
	for (int i = 0; i < _attackedId.size(); i++)
	{
		if (_attackedId[i] == info->attackID)
		{
			alreadyAttacked = true;
			break;
		}
	}
	if (alreadyAttacked) return false; // 이미 피격처리한 공격이라면 피격 처리 안함

	// [2] 피격 판정이 이루어져야하는지 검사
	FloatRect enemyRc = FloatRect(_position, _size, PIVOT::CENTER);
	FloatCircle attackCircle = FloatCircle(circle->origin, circle->size, circle->startRadian, circle->endRadian);

	if (!attackCircle.intersect(enemyRc)) // 호와 사각형의 충돌 검사 함수
	{
		return false; // 피격 판정이 아니므로 피격 처리 안함
	}

	if (_attackedId.size() == 10) // 피격 처리를 해야 하는데 공격 ID 저장 벡터 사이즈가 10이라면
	{
		_attackedId.erase(_attackedId.begin()); // 맨 먼저 들어온 ID를 제거하고
	}
	_attackedId.push_back(info->attackID); // 맨 뒤에 새로운 공격 ID 추가

	return true; // 위 검사 결과 피격 처리가 되어야 함
}

bool Enemy::isHit(Projectile* projectile)
{
	// 2가지 검사를 함
	// 1. 이미 피격 처리를 한 공격인지에 대해 검사
	// 2. 공격 호과 Enemy 렉트의 충돌 여부

	// [1] 이미 피격 처리를 한 공격인지에 대해 검사
	AttackInfo* info = projectile->getAttackInfo();
	bool alreadyAttacked = false;
	for (int i = 0; i < _attackedId.size(); i++)
	{
		if (_attackedId[i] == info->attackID)
		{
			alreadyAttacked = true;
			break;
		}
	}
	if (alreadyAttacked) return false; // 이미 피격처리한 공격이라면 피격 처리 안함

	// [2] 피격 판정이 이루어져야하는지 검사
	FloatRect enemyRc = FloatRect(_position, _size, PIVOT::CENTER);
	FloatRect attackRc = FloatRect(projectile->getPosition(), projectile->getSize(), PIVOT::CENTER);

	if (!FloatRect::intersect(enemyRc, attackRc)) // 사각형과 사각형의 충돌 검사 함수
	{
		return false; // 피격 판정이 아니므로 피격 처리 안함
	}

	if (_attackedId.size() == 10) // 피격 처리를 해야 하는데 공격 ID 저장 벡터 사이즈가 10이라면
	{
		_attackedId.erase(_attackedId.begin()); // 맨 먼저 들어온 ID를 제거하고
	}
	_attackedId.push_back(info->attackID); // 맨 뒤에 새로운 공격 ID 추가

	return true; // 위 검사 결과 피격 처리가 되어야 함
}

bool Enemy::hitEffect(FloatCircle * circle, AttackInfo * info)
{
	_isDetect = true;
	_hit.isHit = true;
	_hit.count = 0;
	//_hit.knockCount = 0;
	_moving.gravity.x = info->knockBack;

	_img = IMAGE_MANAGER->findImage(_imageName + "_Shot");

	DamageInfo damageInfo = info->getDamageInfo();
	Vector2 renderPos = _position;
	renderPos.y -= _size.y * 0.25f;
	renderPos.x += RANDOM->getFromFloatTo(-_size.x * 0.5f, _size.x * 0.5f);
	_enemyManager->showDamage(damageInfo, renderPos);
	_curHp = max(0, _curHp - (damageInfo.damage + damageInfo.trueDamage));

	return true;
}
//
bool Enemy::hitEffect(Projectile * projectile)
{
	AttackInfo* info = projectile->getAttackInfo();
	_isDetect = true;
	_hit.isHit = true;
	_hit.count = 0;
	//_hit.knockCount = 0;
	_moving.gravity.x = info->knockBack;

	_img = IMAGE_MANAGER->findImage(_imageName + "_Shot");

	DamageInfo damageInfo = info->getDamageInfo();
	Vector2 renderPos = _position;
	renderPos.y -= _size.y * 0.25f;
	renderPos.x += RANDOM->getFromFloatTo(-_size.x * 0.5f, _size.x * 0.5f);
	_enemyManager->showDamage(damageInfo, renderPos);
	_curHp = max(0, _curHp - (damageInfo.damage + damageInfo.trueDamage));

	return true;
}
