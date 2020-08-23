#pragma once
#include "Item.h"
#include "NormalProjectile.h"
#include "BoomerangProjectile.h"

class Boomerang : public Item
{
private:
	Animation* _ani;
	Image* _img;
	Image* _aniImg;
	Image* _effect01;

	//Vector2 _position;
	int _minDamage;
	int _maxDamage;
	int _gunType;				//���Ÿ� ���� Ÿ��
	float _renderDegree;
	float _degree;
	float _attackDegree;
	float _returnCount;
	bool _isLeft;
	bool _isAttack;
	bool _activeEffect;
	Vector2 _pos;
	Vector2 _gunPos;
	Vector2 _attackPos;
	Vector2 _effectPos02;

	FloatRect _attackRect;
	int _timeCount;
	int _effectCount;

	float _baseAttackDelay; // ���� ��Ÿ��
	float _currAttackDelay; // ���� ���� ��Ÿ��
	int _maxBullet; // �ִ� �Ѿ� ����
	int _currBullet; // ���� �Ѿ� ����
	float _baseReloadDelay; // ������ ��Ÿ��
	float _currReloadDelay; // ���� ������ ��Ÿ��
	bool _drawEffect; // �̹� render �Լ����� ����Ʈ�� ������ ������ �Ǵ�

	BoomerangProjectile* _projectile;

	AttackInfo* attackInfo02;
public:
	virtual void init() override;
	virtual void release() override;
	virtual void update(Player* player, float const elapsedTime) override;
	virtual void backRender(Player* player) override;
	virtual void frontRender(Player* player) override;
	virtual void displayInfo(); // �κ��丮���� ������ ������

	virtual void attack(Player* player) override; // �÷��̾ ���ݹ�ư�� ������ ȣ��� �Լ�(���ݰ� ������� �������̶�� �� �Լ��� ����)
	virtual void attack(Player* player, FloatRect* rect, AttackInfo* info) override; // ���� ��Ʈ�� �����Ű�� �Լ� 
	virtual void attack(Player* player, FloatCircle* circle, AttackInfo* info) override; // ���� ��Ŭ�� �����Ű�� �Լ�
	virtual void attack(Player* player, Projectile* projectile, AttackInfo* info) override; // źȯ�� �����Ű�� �Լ�

	virtual void getHit(Vector2 const position) override; // �÷��̾ �ǰݵǾ��� �� ȣ��� �Լ�(�ǰݰ� ������� �������̶�� �� �Լ��� ����)

	virtual void equip(Player* player) override; // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ

	int getGunType() { return _gunType; }
};

