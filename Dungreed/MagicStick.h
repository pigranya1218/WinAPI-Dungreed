#pragma once
#include "Item.h"
#include "NormalProjectile.h"

class MagicStick : public Item
{
private:
	Image* _img;

	Image* _reloadEffect;
	Animation* _reloadAni;

	float _currAttackDelay; // ���� ���� ��Ÿ��
	int _maxBullet; // �ִ� �Ѿ� ����
	int _currBullet; // ���� �Ѿ� ����
	float _currReloadDelay; // ���� ������ ��Ÿ��
	bool _drawEffect; // �̹� render �Լ����� ����Ʈ�� ������ ������ �Ǵ�
	bool _oneAttack;
	NormalProjectile* projectile;
	Vector2 renderPosWeapon;
	Vector2 _attackMove;
	float _width;
	float _height;
	FloatRect _hand;
	Vector2 _handSize;
	float _angleOffset;
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

	virtual void reload(Player* player) override; // ������ ��ư�� ������ ȣ��� �Լ�
	virtual void getHit(Vector2 const position) override; // �÷��̾ �ǰݵǾ��� �� ȣ��� �Լ�(�ǰݰ� ������� �������̶�� �� �Լ��� ����)

	virtual void equip(Player* player) override; // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ

	virtual wstring getBulletUI() override;
	virtual float getBulletRatio() override;
};

