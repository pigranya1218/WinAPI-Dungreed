#pragma once
#include "Enemy.h"

class SkelBigIce : public Enemy
{
private:
	tagAttackInfo	_attack;
	tagAttackInfo	_skill;
	tagShootingInfo _shooting;
	int _playCount;
public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);
};

