#pragma once
#include "NormalProjectile.h"
#include "Item.h"

class GatlingGun : public Item
{
private:
	Image* _attackImg;
	Animation* _attackAni;

	Image* _reloadEffect;
	Animation* _reloadAni;

	float _baseAttackDelay; // ���� ��Ÿ��
	float _currAttackDelay; // ���� ���� ��Ÿ��
	int _maxBullet; // �ִ� �Ѿ� ����
	int _currBullet; // ���� �Ѿ� ����
	float _baseReloadDelay; // ������ ��Ÿ��
	float _currReloadDelay; // ���� ������ ��Ÿ��
	bool _drawEffect; // �̹� render �Լ����� ����Ʈ�� ������ ������ �Ǵ�
	bool _isAttack;

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

	virtual void reload(Player* player); // ������ ��ư�� ������ ȣ��� �Լ�
	virtual void getHit(Vector2 const position); // �÷��̾ �ǰݵǾ��� �� ȣ��� �Լ�(�ǰݰ� ������� �������̶�� �� �Լ��� ����)

	virtual void equip(Player* player); // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ

	virtual wstring getBulletUI() override;
	virtual float getBulletRatio() override;
	//NormalProjectile* getBulletInfo();
};

