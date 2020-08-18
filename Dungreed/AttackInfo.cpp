#include "stdafx.h"
#include "AttackInfo.h"

DamageInfo AttackInfo::getDamageInfo()
{
	DamageInfo result;
	result.damage = RANDOM->getFromFloatTo(minDamage, maxDamage);
	int randomCount = RANDOM->getInt(100);
	if (randomCount <= critical) // 크리티컬 발생시
	{
		result.damage *= (1 + criticalDamage * 0.01); // 크리티컬 대미지 합산
	}
	result.trueDamage = trueDamage; // 트루대미지는 크리티컬 영향을 받지 않음

	return result;
}
