#pragma once
#include "Item.h"
class SpikeBall : public Item
{
private:
	int x, y;
	float _angle = PI / 2;

public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void frontRender(Vector2 pos, float angle);
	virtual void backRender(Vector2 pos, float angle);
	virtual void displayInfo(); // �κ��丮���� ������ ������

	virtual void attack(Vector2 const position, float const angle); // �÷��̾ ���ݹ�ư�� ������ ȣ��� �Լ�(���ݰ� ������� �������̶�� �� �Լ��� ����)
	virtual void attack(FloatRect* rect, tagAttackInfo* info); // ���� ��Ʈ�� �����Ű�� �Լ� 
	virtual void attack(FloatCircle* circle, tagAttackInfo* info); // ���� ��Ŭ�� �����Ű�� �Լ�
	virtual void attack(Projectile* projectile, tagAttackInfo* info); // źȯ�� �����Ű�� �Լ�

	virtual void getHit(Vector2 const position); // �÷��̾ �ǰݵǾ��� �� ȣ��� �Լ�(�ǰݰ� ������� �������̶�� �� �Լ��� ����)

	virtual PlayerStat equip(); // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ
};
