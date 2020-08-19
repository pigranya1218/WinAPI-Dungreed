#pragma once
#include "DamageInfo.h"
#include "PlayerStat.h"
#include <set>

class AttackInfo
{
public:
	size_t attackID; // ���� ���̵�, ���ݿ� ���� �ߺ��˻� �Ǻ��� ���ؼ� ���
	set<int> usedItem; // �̰Ϳ� �ݿ��� ������ �ڵ��(�ߺ� �ݿ� ������ ����)

	OBJECT_TEAM team; // ������ ��
	bool madeByWeapon = false; // ���⿡ ���� ����������� �Ǵ� (����ü �Ǵܿ� ����)

	float minDamage = 0; // �ּ� �����
	float maxDamage = 0; // �ִ� �����
	float trueDamage = 0; // Ʈ�� �����
	int critical = 0; // ũ��Ƽ�� Ȯ�� (critical%)
	int criticalDamage = 0; // ũ��Ƽ�� �߰������ ((100 + criticalDamage)%)
	float knockBack = 0; // �˹� (�о�� ��)

public:
	DamageInfo getDamageInfo();
	DamageInfo getDamageInfo(PlayerStat stat);
};

