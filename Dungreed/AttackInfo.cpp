#include "stdafx.h"
#include "AttackInfo.h"

DamageInfo AttackInfo::getDamageInfo()
{
	DamageInfo result;
	int randomCount = RANDOM->getInt(100);

	result.damage = RANDOM->getFromFloatTo(minDamage, maxDamage);
	if (randomCount <= critical) // 크리티컬 발생시
	{
		result.isCritical = true;
		result.damage *= (1 + criticalDamage * 0.01); // 크리티컬 대미지 합산
	}
	result.trueDamage = trueDamage; // 트루대미지는 크리티컬 영향을 받지 않음

	return result;
}

DamageInfo AttackInfo::getDamageInfo(PlayerStat stat)
{
	DamageInfo result;
	int randomCount = RANDOM->getInt(100);

	if (randomCount < stat.block) // 방어하였음
	{
		result.isBlock = true;
	}
	else if (randomCount < stat.evasion) // 회피하였음
	{
		result.isEvade = true;
	}
	else
	{
		result.damage = RANDOM->getFromFloatTo(minDamage, maxDamage);
		if (randomCount <= critical) // 크리티컬 발생시
		{
			result.isCritical = true;
			result.damage *= (1 + criticalDamage * 0.01); // 크리티컬 대미지 합산
		}
		result.damage *= (100 / (100 + stat.defense)); // 방어력 계산
		result.damage = max(0, result.damage - stat.toughness); // 강인함 계산
		result.trueDamage = trueDamage; // 트루대미지
	}

	return result;
}
