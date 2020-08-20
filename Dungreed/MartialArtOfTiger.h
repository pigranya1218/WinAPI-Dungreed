#pragma once
#include "Item.h"
class MartialArtOfTiger : public Item

{
private:
	// ���� ����
	Image* _img;
	Image*	_effect;
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
	float _width;
	float _height;
	
	FloatRect _leftHand;	// �޼�
	FloatRect _rightHand;	// ������
	Vector2 _handSize;		// ���� ũ��
	
	FloatCircle _attackDebug;

public:
	virtual void init();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);

	virtual void attack(Player* player); // �÷��̾ ���ݹ�ư�� ������ ȣ��� �Լ�(���ݰ� ������� �������̶�� �� �Լ��� ����)

	virtual void equip(Player* player); // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ

};


