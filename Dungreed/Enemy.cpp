#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"

void Enemy::tagShootingInfo::fireBullet(EnemyManager * enemyManager)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::ENEMY;

		enemyManager->fireEnemy(bullets[i], attackInfo);
	}
	bulletNum = 0;
}