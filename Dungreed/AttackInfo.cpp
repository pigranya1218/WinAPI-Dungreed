#include "stdafx.h"
#include "AttackInfo.h"

DamageInfo AttackInfo::getDamageInfo()
{
	DamageInfo result;
	result.damage = RANDOM->getFromFloatTo(minDamage, maxDamage);
	int randomCount = RANDOM->getInt(100);
	if (randomCount <= critical) // ũ��Ƽ�� �߻���
	{
		result.damage *= (1 + criticalDamage * 0.01); // ũ��Ƽ�� ����� �ջ�
	}
	result.trueDamage = trueDamage; // Ʈ�������� ũ��Ƽ�� ������ ���� ����

	return result;
}
