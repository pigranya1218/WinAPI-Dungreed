#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"

void Enemy::tagShootingInfo::fireBullet(EnemyManager * enemyManager)
{
	// 생성해논 총알을
	for (int i = 0; i < bullets.size(); i++)
	{
		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::ENEMY;

		// 발사한다.
		enemyManager->fireEnemy(bullets[i], attackInfo);
	}
	// 모두 발사 후 초기화
	bullets.clear();
}