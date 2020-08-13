#pragma once
#include "Enemy.h"

class Ovibos : public Enemy
{
private:
	tagMoveInfo _moving;
	tagAttackInfo _attacking;

	Vector2 _force;
	Vector2 _rushpos;

	bool _break;

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);

	bool playerCollision(const Vector2& playerPos);
};

