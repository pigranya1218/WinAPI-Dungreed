#pragma once
#include "Projectile.h"

// ���������� ���ư��� ����ü��
class NormalProjectile : public Projectile
{
private:
	float		_angleRadian;		// ����ü ���󰡴� ����
	Vector2		_speed;				// ����ü ���󰡴� �ӵ�

	float		_maxTime;			// ����ü ���ӽð�
	float		_count;				// �ð� ����

	Image*		_img;				// ����ü �̹���

	bool		_useAni;			// �ִϸ��̼� ����ϴ°�
	Animation*	_ani;				// ����ü �ִϸ��̼�

	bool		_checkCollision;	// �������� ���� �浹 �˻縦 �ϴ°�
	string		_collisionEffect;	// �ε����� ������ �� ����Ʈ
	Vector2		_effectSize;		// �ε����� ������ �� ����Ʈ ������

	bool		_useGravity;		// �߷� ��� ����
	Vector2		_gravity;			// �߷°�

	bool		_useRotate;			// ����ü�� ���� ���ΰ�

public:
	void init(string imgKey, float angleRadian, float speed, bool useAni, bool isAniLoop, int aniFps, bool isCollision, string collisionEffect, Vector2 effectSize, float range, bool useRotate = 1, bool useGravity = 0);

	virtual void release();
	virtual void update(float elapsedTime);
	virtual void render();

	// �ִϸ��̼� ������Ʈ �Ϸ��� ���� �����ϼ���
	virtual void aniUpdate(float const elapsedTime);
};

