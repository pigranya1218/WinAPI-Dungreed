#pragma once
#include "Enemy.h"
class Ghost : public Enemy
{
private:
	tagAttackInfo _attacking;
	
public:
	void init(const Vector2& pos, DIRECTION direction, bool spawnEffect);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);
};

