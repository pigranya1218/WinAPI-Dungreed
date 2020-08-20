#pragma once
#include "Item.h"

class ShortSpear : public Item
{
private:
	Image* _img;
	// ���� ����
	int	_minDamage;
	int _maxDamage;
	Vector2 _attackMove;
	float _currAttackDelay; // ���� ���� ��Ÿ��
	float _attackAngle;
	bool _reverseMove;
	bool _drawEffect;


	FloatCircle* _attackCircle;
	AttackInfo*	_attackInfo;

public:
	virtual void init() override;
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);

	virtual void attack(Player* player) override; // �÷��̾ ���ݹ�ư�� ������ ȣ��� �Լ�(���ݰ� ������� �������̶�� �� �Լ��� ����)

	virtual void equip(Player* player); // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ
};

