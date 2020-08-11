#pragma once
#include "Item.h"
class MatchLockGun :
	public Item
{
private:
	float _angle;

public:

	void init();
	void release();
	void update(float const elapsedTime);
	void render(Vector2 pos, float angle);
	void displayInfo(); // �κ��丮���� ������ ������

	void attack(Vector2 const position, float const angle); // �÷��̾ ���ݹ�ư�� ������ ȣ��� �Լ�(���ݰ� ������� �������̶�� �� �Լ��� ����)
	void attack(FloatRect* rect, tagAttackInfo* info); // ���� ��Ʈ�� �����Ű�� �Լ� 
	void attack(FloatCircle* circle, tagAttackInfo* info); // ���� ��Ŭ�� �����Ű�� �Լ�
	void attack(Projectile* projectile, tagAttackInfo* info); // źȯ�� �����Ű�� �Լ�

	void getHit(Vector2 const position); // �÷��̾ �ǰݵǾ��� �� ȣ��� �Լ�(�ǰݰ� ������� �������̶�� �� �Լ��� ����)

	PlayerStat equip(); // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ
};

