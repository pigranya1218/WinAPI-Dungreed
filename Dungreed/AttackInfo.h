#pragma once
#include <set>

class AttackInfo
{
public:
	size_t attackID; // ���� ���̵�, ���ݿ� ���� �ߺ��˻� �Ǻ��� ���ؼ� ���
	set<string> _usedItem; // �̰Ϳ� �ݿ��� ������ �ڵ��

	OBJECT_TEAM team; // ������ ��
	float minDamage; // �ּ� �����
	float maxDamage; // �ִ� �����
	int critical; // ũ��Ƽ�� Ȯ��
	int criticalDamage; // ũ��Ƽ�� �߰������
	float knockBack; // �˹� (�о�� ��)
};

