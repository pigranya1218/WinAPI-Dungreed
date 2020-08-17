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
		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::ENEMY;

		// 발사한다.
		if (!bullets.empty())
		{
			enemyManager->fireEnemy(bullets[bullets.size() - 1], attackInfo);
			delete attackInfo;
			//bullets[bullets.size() - 1]->release();
			bullets.pop_back();
		}		
	}	
}