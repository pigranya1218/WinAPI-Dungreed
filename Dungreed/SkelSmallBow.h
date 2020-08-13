#pragma once
#include "Enemy.h"

class SkelSmallBow : public Enemy
{
private:
	AttackInfo	_attack;	// ����
	tagMoveInfo		_moving;	// �̵�
	Animation*		_weaponAni;	// ���� �ִϸ��̼�
	Image*			_weaponImg;	// ���� �̹���

	Vector2			_weaponPos;	// ���� ��ǥ �����

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
};

