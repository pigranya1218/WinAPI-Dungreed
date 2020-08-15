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
			delete attackInfo;
			//bullets[bullets.size() - 1]->release();
			bullets.pop_back();
		}		
	}	
}