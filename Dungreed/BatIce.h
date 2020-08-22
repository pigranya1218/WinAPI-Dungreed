#pragma once
#include "Enemy.h"

class BatIce : public Enemy
{
private:
	tagShootingInfo	_shooting;
	int _enterCount;
public:
	void init(const Vector2& pos, DIRECTION direction, bool spawnEffect);
	void release();
	void update(float const timeElapsed);
	void render();
	int _PlayCount;
	void setState(ENEMY_STATE state);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);
};

