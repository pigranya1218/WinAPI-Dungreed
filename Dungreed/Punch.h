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
	float _currAttackDelay; // ���� ���� ��Ÿ��
	float _attackAngle;
	bool _reverseMove;

	// �� �̹��� ����
	FloatRect _leftHand;	// �޼�
	FloatRect _rightHand;	// ������
	Vector2 _handSize;		// ���� ũ��

	FloatCircle* _attackCircle;
	AttackInfo*	_attackInfo;

public:
	virtual void init();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);

	virtual void attack(Player* player); // �÷��̾ ���ݹ�ư�� ������ ȣ��� �Լ�(���ݰ� ������� �������̶�� �� �Լ��� ����)

	virtual void equip(Player* player) override; // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ
};

