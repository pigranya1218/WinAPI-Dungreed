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
	bool _isLeft;
	Vector2 _gunPos;
	bool _isAttack;
	FloatRect _attackRect;
	int _timeCount;
public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render(Vector2 pos, float angle);
	virtual void displayInfo(); // �κ��丮���� ������ ������

	virtual void attack(Vector2 const position, float const angle); // �÷��̾ ���ݹ�ư�� ������ ȣ��� �Լ�(���ݰ� ������� �������̶�� �� �Լ��� ����)
	virtual void attack(FloatRect* rect, AttackInfo* info); // ���� ��Ʈ�� �����Ű�� �Լ� 
	virtual void attack(FloatCircle* circle, AttackInfo* info); // ���� ��Ŭ�� �����Ű�� �Լ�
	virtual void attack(Projectile* projectile, AttackInfo* info); // źȯ�� �����Ű�� �Լ�

	virtual void getHit(Vector2 const position); // �÷��̾ �ǰݵǾ��� �� ȣ��� �Լ�(�ǰݰ� ������� �������̶�� �� �Լ��� ����)

	virtual void equip(Player* player); // �������� �������� �� ȣ��� �Լ�, ������ ��� �ٲ����ϴ��� ��ȯ
	int getGunType() { return _gunType; }
};

