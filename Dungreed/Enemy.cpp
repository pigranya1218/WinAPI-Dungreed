#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"

void Enemy::tagShootingInfo::fireBullet(EnemyManager * enemyManager, int fireCount)
{
	if (bullets.empty()) return;

	int fireLoop = (fireCount == 0) ? (bullets.size()) : (fireCount);

	// �����س��� �Ѿ���
	for (int i = 0; i < fireLoop; i++)
	{
		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::ENEMY;

		// �߻��Ѵ�.
		if (!bullets.empty())
		{
			enemyManager->fireEnemy(bullets[bullets.size() - 1], attackInfo);
			// delete attackInfo;
			//bullets[bullets.size() - 1]->release();
			bullets.pop_back();
		}		
	}	
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
