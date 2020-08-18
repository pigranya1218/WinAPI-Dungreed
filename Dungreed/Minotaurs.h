#pragma once
#include "Enemy.h"
#include <dxgitype.h>

class Minotaurs : public Enemy
{
private:
	tagAttackInfo	_skill;		// 돌진 모션
	tagAttackInfo	_attack;	// 도끼 휘두르는 모션

	Vector2			_lastPos;	// 이전 좌표
	Vector2			_currPos;	// 현재 좌표
	Vector2			_rushPos;	// 돌진 시작 포지션

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);

	bool playerCollision(const Vector2& playerPos);
};

