#pragma once
#include "Item.h"
class Boomerang :
	public Item
{
private:
	Animation* _ani;
	Image* _img;
	Image* _aniImg;
	Image* _effect01;

	Vector2 _position;
	int _minDamage;
	int _maxDamage;
	int _gunType;				//���Ÿ� ���� Ÿ��
	float _angle;
	float _renderDegree;
	float _degree;
	bool _isLeft;
	Vector2 _pos;
	Vector2 _gunPos;
	Vector2 _attackPos;
	bool _isAttack;
	FloatRect _attackRect;
	int _timeCount;
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

	virtual void dash(Player* player) {}; // �÷��̾ �뽬���� ��
	virtual void reload(Player* player) {}; // �÷��̾ ��������ư�� ������ ��
	
	virtual void getHit(Vector2 const position); // �÷��̾ �ǰݵǾ��� �� ȣ��� �Լ�(�ǰݰ� ������� �������̶�� �� �Լ��� ����)

	virtual PlayerStat equip(); // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ
	int getGunType() { return _gunType; }
};

