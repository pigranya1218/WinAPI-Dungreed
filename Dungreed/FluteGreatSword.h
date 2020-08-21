#pragma once
#include "Item.h"
class FluteGreatSword : public Item
{
private:
	struct tagAttack
	{
		FloatCircle* _attackCircle;
		AttackInfo* _attackInfo;
		float _hitDelay;
		int _count;
	};

private:

	vector<tagAttack> _VtagAttack;

	// ���� ����
	Image*	_effect;
	Image* _img;
	int	_minDamage;
	int _maxDamage;
	Vector2 _attackMove;
	float _baseAttackDelay; // ���� ��Ÿ��
	float _currAttackDelay; // ���� ���� ��Ÿ��
	float _attackAngle;
	float _angleOffset;
	bool _reverseMove;
	bool _drawEffect;
	bool _oneAttack;
	bool _back;
	bool _isBroken;
	FloatRect _hand;
	Vector2 _handSize;
	Animation* _ani;
	float _width;
	float _height;

	FloatCircle _attackDebug;
public:
	virtual void init();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);

	virtual void attack(Player* player); // �÷��̾ ���ݹ�ư�� ������ ȣ��� �Լ�(���ݰ� ������� �������̶�� �� �Լ��� ����)

	virtual void equip(Player* player); // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ

};

