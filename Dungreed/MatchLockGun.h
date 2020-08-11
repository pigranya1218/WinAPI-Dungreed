#pragma once
#include "Item.h"
#include "GunBullet.h"

class MatchLockGun : public Item
{
private:

	Image* _shootEffect;
	Image* _dustEffect;
	Animation* _effectAni01;
	Animation* _effectAni02;

	int _minDamage;
	int _maxDamage;
	int _gunType;				//���Ÿ� ���� Ÿ��
	float _angle;
	bool _isLeft;
	Vector2 _gunPos;

	bool _isAttack;

	GunBullet* _bullet;
public:

	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render(Vector2 pos, float angle);
	virtual void displayInfo(); // �κ��丮���� ������ ������

	virtual void attack(Vector2 const position, float const angle); // �÷��̾ ���ݹ�ư�� ������ ȣ��� �Լ�(���ݰ� ������� �������̶�� �� �Լ��� ����)
	virtual void attack(FloatRect* rect, tagAttackInfo* info); // ���� ��Ʈ�� �����Ű�� �Լ� 
	virtual void attack(FloatCircle* circle, tagAttackInfo* info); // ���� ��Ŭ�� �����Ű�� �Լ�
	virtual void attack(Projectile* projectile, tagAttackInfo* info); // źȯ�� �����Ű�� �Լ�

	virtual void getHit(Vector2 const position); // �÷��̾ �ǰݵǾ��� �� ȣ��� �Լ�(�ǰݰ� ������� �������̶�� �� �Լ��� ����)

	virtual PlayerStat equip(); // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ
	int getGunType() { return _gunType; }
};

