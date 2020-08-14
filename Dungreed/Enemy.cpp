#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"

void Enemy::tagShootingInfo::fireBullet(EnemyManager * enemyManager)
{
	// �����س� �Ѿ���
	for (int i = 0; i < bullets.size(); i++)
	{
		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::ENEMY;

		// �߻��Ѵ�.
		enemyManager->fireEnemy(bullets[i], attackInfo);
	}
	// ��� �߻� �� �ʱ�ȭ
	bullets.clear();
}