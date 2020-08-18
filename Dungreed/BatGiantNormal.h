#pragma once
#include "Enemy.h"

class BatGiantNormal : public Enemy
{
private:
	tagShootingInfo _shooting;	// 탄막 관련
	tagAttackInfo	_attack;	// 공격 관련

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

