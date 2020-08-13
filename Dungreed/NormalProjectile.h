#pragma once
#include "Projectile.h"

// ���������� ���ư��� ����ü��
class NormalProjectile : public Projectile
{
private:
	float _angleRadian;			// ����ü ���󰡴� ����
	float _speed;				// ����ü ���󰡴� �ӵ�
	
	Image* _img;				// ����ü �̹���

	bool _useAni;				// �ִϸ��̼� ����ϴ°�
	Animation* _ani;			// ����ü �ִϸ��̼�

	bool _checkCollision;			// �������� ���� �浹 �˻縦 �ϴ°�
	string _collisionEffect;	// �ε����� ������ �� ����Ʈ
	Vector2 _effectSize;		// �ε����� ������ �� ����Ʈ ������

public:
	void init(string imgKey, float angleRadian, float speed, bool useAni, bool isAniLoop, int aniFps, bool isCollision, string collisionEffect, Vector2 effectSize);
	virtual void release();
	virtual void update(float elapsedTime);
	virtual void render();
};

