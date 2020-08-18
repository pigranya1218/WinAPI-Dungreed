#pragma once
#include "DamageInfo.h"
//#include <set>

class AttackInfo
{
public:
	size_t attackID; // ���� ���̵�, ���ݿ� ���� �ߺ��˻� �Ǻ��� ���ؼ� ���
	//set<int> _usedItem; // �̰Ϳ� �ݿ��� ������ �ڵ��

	OBJECT_TEAM team; // ������ ��
	float minDamage = 0; // �ּ� �����
	float maxDamage = 0; // �ִ� �����
	float trueDamage = 0; // Ʈ�� �����
	int critical = 0; // ũ��Ƽ�� Ȯ�� (critical%)
	int criticalDamage = 0; // ũ��Ƽ�� �߰������ ((100 + criticalDamage)%)
	float knockBack = 0; // �˹� (�о�� ��)

public:
	//~AttackInfo() {/* if (!_usedItem.empty()) { _usedItem.clear(); } */}
	DamageInfo getDamageInfo();
};

