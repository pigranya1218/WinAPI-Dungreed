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
		// �߻��Ѵ�.
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
