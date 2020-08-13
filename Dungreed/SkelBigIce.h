#pragma once
#include "Enemy.h"

class SkelBigIce : public Enemy
{
private:
	tagMoveInfo		_moving;

	AttackInfo	_attack;
	AttackInfo	_skill;

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
};

