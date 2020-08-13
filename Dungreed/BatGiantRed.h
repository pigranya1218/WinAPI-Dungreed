#pragma once
#include "Enemy.h"

class BatGiantRed : public Enemy
{
private:
	AttackInfo	_shooting;	// 공격 관련
	tagMoveInfo		_moving;	// 이동 관련

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
};

