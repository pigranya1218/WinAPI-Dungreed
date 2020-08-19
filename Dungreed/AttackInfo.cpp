#include "stdafx.h"
#include "AttackInfo.h"

DamageInfo AttackInfo::getDamageInfo()
{
	DamageInfo result;
	int randomCount = RANDOM->getInt(100);

	result.damage = RANDOM->getFromFloatTo(minDamage, maxDamage);
	if (randomCount <= critical) // ũ��Ƽ�� �߻���
	{
		result.isCritical = true;
		result.damage *= (1 + criticalDamage * 0.01); // ũ��Ƽ�� ����� �ջ�
	}
	result.trueDamage = trueDamage; // Ʈ�������� ũ��Ƽ�� ������ ���� ����

	return result;
}

DamageInfo AttackInfo::getDamageInfo(PlayerStat stat)
{
	DamageInfo result;
	int randomCount = RANDOM->getInt(100);

	if (randomCount < stat.block) // ����Ͽ���
	{
		result.isBlock = true;
	}
	else if (randomCount < stat.evasion) // ȸ���Ͽ���
	{
		result.isEvade = true;
	}
	else
	{
		result.damage = RANDOM->getFromFloatTo(minDamage, maxDamage);
		if (randomCount <= critical) // ũ��Ƽ�� �߻���
		{
			result.isCritical = true;
			result.damage *= (1 + criticalDamage * 0.01); // ũ��Ƽ�� ����� �ջ�
		}
		result.damage *= (100 / (100 + stat.defense)); // ���� ���
		result.damage = max(0, result.damage - stat.toughness); // ������ ���
		result.trueDamage = trueDamage; // Ʈ������
	}

	return result;
}
