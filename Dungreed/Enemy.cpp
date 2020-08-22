#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"

void Enemy::tagShootingInfo::fireBullet(int enemyCode, EnemyManager * enemyManager, int fireCount)
{
	if (bullets.empty()) return;

	int fireLoop = (fireCount == 0) ? (bullets.size()) : (fireCount);
	string attackCode = to_string(enemyCode) + to_string(TIME_MANAGER->getWorldTime());
	size_t attackId = TTYONE_UTIL::getHash(attackCode);

	// �����س��� �Ѿ���
	for (int i = 0; i < fireLoop; i++)
	{
		// �߻��Ѵ�.
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
	// 2���� �˻縦 ��
	// 1. �̹� �ǰ� ó���� �� ���������� ���� �˻�
	// 2. ���� ��Ʈ�� Enemy ��Ʈ�� �浹 ����

	// [1] �̹� �ǰ� ó���� �� ���������� ���� �˻�
	bool alreadyAttacked = false;
	for (int i = 0; i < _attackedId.size(); i++)
	{
		if (_attackedId[i] == info->attackID)
		{
			alreadyAttacked = true;
			break;
		}
	}
	if (alreadyAttacked) return false; // �̹� �ǰ�ó���� �����̶�� �ǰ� ó�� ����

	// [2] �ǰ� ������ �̷�������ϴ��� �˻�
	FloatRect enemyRc = FloatRect(_position, _size, PIVOT::CENTER);
	FloatRect attackRc = FloatRect(rc->getCenter(), rc->getSize(), PIVOT::CENTER);

	if (!FloatRect::intersect(enemyRc, attackRc)) // �簢���� �簢���� �浹 �˻� �Լ�
	{
		return false; // �ǰ� ������ �ƴϹǷ� �ǰ� ó�� ����
	}

	if (_attackedId.size() == 10) // �ǰ� ó���� �ؾ� �ϴµ� ���� ID ���� ���� ����� 10�̶��
	{
		_attackedId.erase(_attackedId.begin()); // �� ���� ���� ID�� �����ϰ�
		_attackedId.push_back(info->attackID); // �� �ڿ� ���ο� ���� ID �߰�
	}

	return true; // �� �˻� ��� �ǰ� ó���� �Ǿ�� ��
}

bool Enemy::isHit(FloatCircle* circle, AttackInfo* info)
{
	// 2���� �˻縦 ��
	// 1. �̹� �ǰ� ó���� �� ���������� ���� �˻�
	// 2. ���� ȣ�� Enemy ��Ʈ�� �浹 ����

	// [1] �̹� �ǰ� ó���� �� ���������� ���� �˻�
	bool alreadyAttacked = false;
	for (int i = 0; i < _attackedId.size(); i++)
	{
		if (_attackedId[i] == info->attackID)
		{
			alreadyAttacked = true;
			break;
		}
	}
	if (alreadyAttacked) return false; // �̹� �ǰ�ó���� �����̶�� �ǰ� ó�� ����

	// [2] �ǰ� ������ �̷�������ϴ��� �˻�
	FloatRect enemyRc = FloatRect(_position, _size, PIVOT::CENTER);
	FloatCircle attackCircle = FloatCircle(circle->origin, circle->size, circle->startRadian, circle->endRadian);

	if (!attackCircle.intersect(enemyRc)) // ȣ�� �簢���� �浹 �˻� �Լ�
	{
		return false; // �ǰ� ������ �ƴϹǷ� �ǰ� ó�� ����
	}

	if (_attackedId.size() == 10) // �ǰ� ó���� �ؾ� �ϴµ� ���� ID ���� ���� ����� 10�̶��
	{
		_attackedId.erase(_attackedId.begin()); // �� ���� ���� ID�� �����ϰ�
	}
	_attackedId.push_back(info->attackID); // �� �ڿ� ���ο� ���� ID �߰�

	return true; // �� �˻� ��� �ǰ� ó���� �Ǿ�� ��
}

bool Enemy::isHit(Projectile* projectile)
{
	// 2���� �˻縦 ��
	// 1. �̹� �ǰ� ó���� �� ���������� ���� �˻�
	// 2. ���� ȣ�� Enemy ��Ʈ�� �浹 ����

	// [1] �̹� �ǰ� ó���� �� ���������� ���� �˻�
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
	if (alreadyAttacked) return false; // �̹� �ǰ�ó���� �����̶�� �ǰ� ó�� ����

	// [2] �ǰ� ������ �̷�������ϴ��� �˻�
	FloatRect enemyRc = FloatRect(_position, _size, PIVOT::CENTER);
	FloatRect attackRc = FloatRect(projectile->getPosition(), projectile->getSize(), PIVOT::CENTER);

	if (!FloatRect::intersect(enemyRc, attackRc)) // �簢���� �簢���� �浹 �˻� �Լ�
	{
		return false; // �ǰ� ������ �ƴϹǷ� �ǰ� ó�� ����
	}

	if (_attackedId.size() == 10) // �ǰ� ó���� �ؾ� �ϴµ� ���� ID ���� ���� ����� 10�̶��
	{
		_attackedId.erase(_attackedId.begin()); // �� ���� ���� ID�� �����ϰ�
	}
	_attackedId.push_back(info->attackID); // �� �ڿ� ���ο� ���� ID �߰�

	return true; // �� �˻� ��� �ǰ� ó���� �Ǿ�� ��
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
	// �̸� �Ҵ�
	FloatCircle* circle = new FloatCircle;
	AttackInfo* attackInfo = new AttackInfo;

	// ���� �� ����
	circle->origin = pos;
	circle->size = circleSize;
	circle->startRadian = startRad;
	circle->endRadian = endRad;

	// ���� ���� ����
	attackInfo->team = OBJECT_TEAM::ENEMY;
	attackInfo->minDamage = info.minDamage;
	attackInfo->maxDamage = info.maxDamage;
	attackInfo->knockBack = info.knockBack;
	attackInfo->trueDamage = info.trueDamage;
	attackInfo->critical = info.critical;
	attackInfo->criticalDamage = info.criticalDamage;

	// ���� ���̵� �ߺ� ������
	if (id.empty())
	{
		// ���� ���̵� ����
		id = to_string(enemyCode) + to_string(TIME_MANAGER->getWorldTime());
	}
	// �ؽü���
	attackInfo->attackID = TTYONE_UTIL::getHash(id);

	// ���� �� �����
	circleDebug = FloatCircle(pos, circleSize, startRad, endRad);

	// ���� ����
	enemyManager->attack(circle, attackInfo);

	// �޸� ����
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
