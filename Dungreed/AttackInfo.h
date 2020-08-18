#pragma once
#include "DamageInfo.h"
#include <set>

class AttackInfo
{
public:
	size_t attackID; // ���� ���̵�, ���ݿ� ���� �ߺ��˻� �Ǻ��� ���ؼ� ���
	set<string> _usedItem; // �̰Ϳ� �ݿ��� ������ �ڵ��

	OBJECT_TEAM team; // ������ ��
	float minDamage; // �ּ� �����
	float maxDamage; // �ִ� �����
	float trueDamage; // Ʈ�� �����
	int critical; // ũ��Ƽ�� Ȯ�� (critical%)
	int criticalDamage; // ũ��Ƽ�� �߰������ ((100 + criticalDamage)%)
	float knockBack; // �˹� (�о�� ��)

public:
	DamageInfo getDamageInfo();
};

