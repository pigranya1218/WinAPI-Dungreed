#pragma once
#include "NormalProjectile.h"
class HeartOfCosmosProjectile : public NormalProjectile
{
private:
	float		_angleRadian;		// ����ü ���󰡴� ����
	float		_speed;				// ����ü ���󰡴� �ӵ�

	float		_maxTime;			// ����ü ���ӽð�
	float		_count;				// �ð� ����

	Image*		_img;				// ����ü �̹���

	bool		_useAni;			// �ִϸ��̼� ����ϴ°�
	Animation*	_ani;				// ����ü �ִϸ��̼�

	bool		_checkCollision;	// �������� ���� �浹 �˻縦 �ϴ°�
	string		_collisionEffect;	// �ε����� ������ �� ����Ʈ
	Vector2		_effectSize;		// �ε����� ������ �� ����Ʈ ������

	bool		_useRotate;			// ����ü�� ���� ���ΰ�


public:
	void init(string imgKey, float angleRadian, float speed, bool useAni, bool isAniLoop, int aniFps, bool isCollision, string collisionEffect, Vector2 effectSize, float maxTime, bool useRotate = 1);
	virtual void release();
	virtual void update(float elapsedTime);
	virtual void render();

	// �ִϸ��̼� ������Ʈ �Ϸ��� ���� �����ϼ���
	virtual void aniUpdate(float const elapsedTime);
};

