#pragma once
#include "Enemy.h"

class SkelBigIce : public Enemy
{
private:
	tagAttackInfo _attack;

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update();
	void render();

	void setState(ENEMY_STATE state);
};

