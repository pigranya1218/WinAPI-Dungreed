#pragma once
#include "Enemy.h"

class SkelSmallDagger : public Enemy
{
private:
	tagMoveInfo		_moving;	// 이동 관련
	tagAttackInfo	_attack;	// 공격 관련

	Image*			_weaponImg;	// 무기 이미지
	Animation*		_weaponAni;	// 무기 애니메이션

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
};

