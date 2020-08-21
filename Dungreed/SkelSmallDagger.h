#pragma once
#include "Enemy.h"

class SkelSmallDagger : public Enemy
{
private:
	tagAttackInfo	_attack;	// ���� ����

	Image*			_weaponImg;	// ���� �̹���
	Animation*		_weaponAni;	// ���� �ִϸ��̼�
	int count;
public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);
};

