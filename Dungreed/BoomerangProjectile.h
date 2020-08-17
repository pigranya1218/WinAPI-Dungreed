#pragma once
#include "Projectile.h"

class BoomerangProjectile :	public Projectile
{
private:
	float		_angleRadian;		// ����ü ���󰡴� ����
	float		_speed;				// ����ü ���󰡴� �ӵ�
	
	float		_radius;			// �浹��

	float		_range;				// ����ü �����Ÿ�
	Vector2		_startPos;			// ����ü ������ġ

	Image*		_img;				// ����ü �̹���

	bool		_useAni;			// �ִϸ��̼� ����ϴ°�
	Animation*	_ani;				// ����ü �ִϸ��̼�

	bool		_checkCollision;	// �������� ���� �浹 �˻縦 �ϴ°�
	string		_collisionEffect;	// �ε����� ������ �� ����Ʈ
	Vector2		_effectSize;		// �ε����� ������ �� ����Ʈ ������

	bool _useRotate;				// ����ü�� ���� ���ΰ�
	bool _ProjectileReturn;

public:
	void init(string imgKey, float angleRadian, float speed, bool useAni, bool isAniLoop, int aniFps, string collisionEffect, Vector2 effectSize, float range, bool useRotate = 1);
	virtual void release();
	virtual void update(float elapsedTime);
	virtual void render();

	// �ִϸ��̼� ������Ʈ �Ϸ��� ���� �����ϼ���
	virtual void aniUpdate(float const elapsedTime);
	float getRadius() { return _radius; }
	bool getReturn() { return _ProjectileReturn; }
};

