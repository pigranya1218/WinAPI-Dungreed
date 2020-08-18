#pragma once
#include "Enemy.h"

class SkelSmallBow : public Enemy
{
private:
	tagAttackInfo	_attack;		// 공격
	tagShootingInfo _shooting;		// 화살
	Animation*		_weaponAni;		// 무기 애니메이션
	Image*			_weaponImg;		// 무기 이미지

	Image*			_handImg;		// 손 이미지

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);
};

