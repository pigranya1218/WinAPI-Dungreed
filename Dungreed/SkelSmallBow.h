#pragma once
#include "Enemy.h"

class SkelSmallBow : public Enemy
{
private:
	AttackInfo	_attack;	// 공격
	tagMoveInfo		_moving;	// 이동
	Animation*		_weaponAni;	// 무기 애니메이션
	Image*			_weaponImg;	// 무기 이미지

	Vector2			_weaponPos;	// 무기 좌표 저장용

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
};

