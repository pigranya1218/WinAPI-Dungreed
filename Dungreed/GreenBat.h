#pragma once
#include"Item.h"
class GreenBat :public Item
{
private:
	Vector2 renderPos;
	int x, y;
	Animation* _ani1;
	DIRECTION _direction;

public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);
	virtual void displayInfo(); // �κ��丮���� ������ ������

	virtual void attack(Player* player); // �÷��̾ ���ݹ�ư�� ������ ȣ��� �Լ�(���ݰ� ������� �������̶�� �� �Լ��� ����)
	virtual void attack(FloatRect* rect, tagAttackInfo* info); // ���� ��Ʈ�� �����Ű�� �Լ� 
	virtual void attack(FloatCircle* circle, tagAttackInfo* info); // ���� ��Ŭ�� �����Ű�� �Լ�
	virtual void attack(Projectile* projectile, tagAttackInfo* info); // źȯ�� �����Ű�� �Լ�

	virtual void getHit(Vector2 const position); // �÷��̾ �ǰݵǾ��� �� ȣ��� �Լ�(�ǰݰ� ������� �������̶�� �� �Լ��� ����)

	virtual PlayerStat equip(); // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ
};

