#pragma once
#include "Enemy.h"

class SkelSmallDagger : public Enemy
{
private:
	tagMoveInfo		_moving;	// �̵� ����
	tagAttackInfo	_attack;	// ���� ����

	Image*			_weaponImg;	// ���� �̹���
	Animation*		_weaponAni;	// ���� �ִϸ��̼�

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
};

