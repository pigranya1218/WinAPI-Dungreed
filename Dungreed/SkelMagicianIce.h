#pragma once
#include "Enemy.h"

class SkelMagicianIce : public Enemy
{
private:
	tagAttackInfo	_attack;	// 공격

	Image*			_attackImg;	// 공격 이펙트 이미지
	Animation*		_attackAni;	// 공격 이펙트 프레임
	Vector2			_attackPos;	// 공격 이펙트 좌표 저장용

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
};

