#pragma once
#include "Item.h"
class Voluspa : public Item
{
private:
	Image* _img;
	Vector2 renderPos;
	Vector2 location;
	bool Opposition;
	float _currAttackDelay;
public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);
	virtual void displayInfo(); // �κ��丮���� ������ ������

	virtual void attack(Player* player); // �÷��̾ ���ݹ�ư�� ������ ȣ��� �Լ�(���ݰ� ������� �������̶�� �� �Լ��� ����)
	virtual void attack(FloatRect* rect, AttackInfo* info); // ���� ��Ʈ�� �����Ű�� �Լ� 
	virtual void attack(FloatCircle* circle, AttackInfo* info); // ���� ��Ŭ�� �����Ű�� �Լ�
	virtual void attack(Projectile* projectile, AttackInfo* info); // źȯ�� �����Ű�� �Լ�

	virtual void getHit(Vector2 const position); // �÷��̾ �ǰݵǾ��� �� ȣ��� �Լ�(�ǰݰ� ������� �������̶�� �� �Լ��� ����)

	virtual PlayerStat equip(); // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ
};
