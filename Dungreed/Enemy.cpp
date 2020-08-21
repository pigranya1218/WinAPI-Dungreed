#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"

void Enemy::tagShootingInfo::fireBullet(int enemyCode, EnemyManager * enemyManager, int fireCount)
{
	if (bullets.empty()) return;

	int fireLoop = (fireCount == 0) ? (bullets.size()) : (fireCount);
	string attackCode = to_string(enemyCode) + to_string(TIME_MANAGER->getWorldTime());
	size_t attackId = TTYONE_UTIL::getHash(attackCode);

	// 생성해놓은 총알을
	for (int i = 0; i < fireLoop; i++)
	{
		// 발사한다.
		if (!bullets.empty())
		{
			AttackInfo* attackInfo = new AttackInfo;	
			attackInfo->attackID = attackId;
			attackInfo->minDamage = info.minDamage;
			attackInfo->maxDamage = info.maxDamage;
			attackInfo->trueDamage = info.trueDamage;
			attackInfo->knockBack = info.knockBack;
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
	SOUND_MANAGER->play("Enemy/Die", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
	Vector2 drawSize = _img->getFrameSize() * _scale;
	drawSize.x = drawSize.y = max(drawSize.x, drawSize.y);
	EFFECT_MANAGER->play("Enemy_Destroy", _position, drawSize);
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
	if (_state == ENEMY_STATE::ENTER) return false;

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
	if (_state == ENEMY_STATE::ENTER) return false;

	AttackInfo* info = projectile->getAttackInfo();
	_isDetect = true;
	_hit.isHit = true;
	_hit.count = 0;
	//_hit.knockCount = 0;
	_moving.gravity.x = info->knockBack;
	SOUND_MANAGER->play("Enemy/GetHit", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));

	_img = IMAGE_MANAGER->findImage(_imageName + "_Shot");

	DamageInfo damageInfo = info->getDamageInfo();
	Vector2 renderPos = _position;
	renderPos.y -= _size.y * 0.25f;
	renderPos.x += RANDOM->getFromFloatTo(-_size.x * 0.5f, _size.x * 0.5f);
	_enemyManager->showDamage(damageInfo, renderPos);
	_curHp = max(0, _curHp - (damageInfo.damage + damageInfo.trueDamage));

	return true;
}

void Enemy::tagAttackInfo::attackCircle(int enemyCode, EnemyManager * enemyManager, const Vector2& pos, const float startRad, const float endRad)
{
	// 미리 할당
	FloatCircle* circle = new FloatCircle;
	AttackInfo* attackInfo = new AttackInfo;

	// 공격 원 설정
	circle->origin = pos;
	circle->size = circleSize;
	circle->startRadian = startRad;
	circle->endRadian = endRad;

	// 공격 정보 설정
	attackInfo->team = OBJECT_TEAM::ENEMY;
	attackInfo->minDamage = info.minDamage;
	attackInfo->maxDamage = info.maxDamage;
	attackInfo->knockBack = info.knockBack;
	attackInfo->trueDamage = info.trueDamage;
	attackInfo->critical = info.critical;
	attackInfo->criticalDamage = info.criticalDamage;

	// 공격 아이디 중복 방지용
	if (id.empty())
	{
		// 공격 아이디 설정
		id = to_string(enemyCode) + to_string(TIME_MANAGER->getWorldTime());
	}
	// 해시설정
	attackInfo->attackID = TTYONE_UTIL::getHash(id);

	// 공격 원 디버그
	circleDebug = FloatCircle(pos, circleSize, startRad, endRad);

	// 공격 전달
	enemyManager->attack(circle, attackInfo);

	// 메모리 해제
	SAFE_DELETE(circle);
	SAFE_DELETE(attackInfo);
}

void Enemy::tagAttackInfo::attackRect(int enemyCode, EnemyManager* enemyManager, FloatRect rc)
{
	FloatRect* attackRc = new FloatRect;
	AttackInfo* attackInfo = new AttackInfo;

	*attackRc = rectMakePivot(rc.getCenter(), rc.getSize(), PIVOT::CENTER);

	attackInfo->team = OBJECT_TEAM::ENEMY;
	attackInfo->minDamage = info.minDamage;
	attackInfo->maxDamage = info.maxDamage;
	attackInfo->knockBack = info.knockBack;
	attackInfo->trueDamage = info.trueDamage;
	attackInfo->critical = info.critical;
	attackInfo->criticalDamage = info.criticalDamage;

	if (id.empty())
	{
		id = to_string(enemyCode) + to_string(TIME_MANAGER->getWorldTime());
	}
	attackInfo->attackID = TTYONE_UTIL::getHash(id);

	rectDebug = FloatRect(rc.getCenter(), rc.getSize(), PIVOT::CENTER);

	enemyManager->attack(attackRc, attackInfo);

	SAFE_DELETE(attackRc);
	SAFE_DELETE(attackInfo);
}
