#pragma once
#include "Enemy.h"
#include <dxgitype.h>

class Minotaurs : public Enemy
{
private:
	tagAttackInfo	_skill;		// ���� ���
	tagAttackInfo	_attack;	// ���� �ֵθ��� ���

	Vector2			_lastPos;	// ���� ��ǥ
	Vector2			_currPos;	// ���� ��ǥ
	Vector2			_rushPos;	// ���� ���� ������

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);

	bool playerCollision(const Vector2& playerPos);
};

