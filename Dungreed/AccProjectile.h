#pragma once
#include "NormalProjectile.h"
class AccProjectile : public NormalProjectile
{
private:
	Vector2		_pos;	            // ����ü ��ǥ
	float		_speed;				// ����ü ���󰡴� �ӵ�

	float		_maxTime;			// ����ü ���ӽð�
	float		_count;				// �ð� ����
	bool		_collsionGround;	// ���� �� �浹 ����
	bool		_collisionPlatForm;	// Ǫ�� �� �浹 ����
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
	void init(string imgKey, Vector2 pos, float speed, bool useAni, bool isAniLoop, int aniFps, bool isCollision, string collisionEffect, Vector2 effectSize, float maxTime, bool useRotate = 1, bool collsionGround = 1, bool collsionPlatForm = 1, bool useGravity = 0);
	virtual void release();
	virtual void update(float elapsedTime);
	virtual void render();

	// �ִϸ��̼� ������Ʈ �Ϸ��� ���� �����ϼ���
	virtual void aniUpdate(float const elapsedTime);
};

