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
	virtual void backRender(Vector2 pos, float angle);
	virtual void frontRender(Vector2 pos, float angle);
	virtual void displayInfo(); // �κ��丮���� ������ ������

	virtual void attack(Vector2 const position, float const angle); // �÷��̾ ���ݹ�ư�� ������ ȣ��� �Լ�(���ݰ� ������� �������̶�� �� �Լ��� ����)
	virtual void attack(FloatRect* rect, tagAttackInfo* info); // ���� ��Ʈ�� �����Ű�� �Լ� 
	virtual void attack(FloatCircle* circle, tagAttackInfo* info); // ���� ��Ŭ�� �����Ű�� �Լ�
	virtual void attack(Projectile* projectile, tagAttackInfo* info); // źȯ�� �����Ű�� �Լ�

	virtual void getHit(Vector2 const position); // �÷��̾ �ǰݵǾ��� �� ȣ��� �Լ�(�ǰݰ� ������� �������̶�� �� �Լ��� ����)

	//virtual PlayerStat equip(); // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ
};

