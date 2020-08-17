#pragma once
#include "Item.h"

class Punch : public Item
{
private:
	// ���� ����
	Image*	_effect;
	int	_minDamage;
	int _maxDamage;
	Vector2 _attackMove;
	float _baseAttackDelay; // ���� ��Ÿ��
	float _currAttackDelay; // ���� ���� ��Ÿ��
	float _attackAngle;
	bool _reverseMove;

	// �� �̹��� ����
	FloatRect _leftHand;	// �޼�
	FloatRect _rightHand;	// ������
	Vector2 _handSize;		// ���� ũ��

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

	virtual void equip(Player* player); // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ
};

