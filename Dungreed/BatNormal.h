#pragma once
#include "Enemy.h"

class BatNormal : public Enemy
{
private:
	tagMoveInfo		_moving;

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
};
