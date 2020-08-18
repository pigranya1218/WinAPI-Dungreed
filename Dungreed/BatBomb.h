#pragma once
#include "Enemy.h"

class BatBomb : public Enemy
{
private:
	tagAttackInfo	_attack;

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);

	bool hitEffect(FloatRect* rc, AttackInfo* info);
	bool hitEffect(FloatCircle* circle, AttackInfo* info);
	bool hitEffect(Projectile* projectile, AttackInfo* info);
};

