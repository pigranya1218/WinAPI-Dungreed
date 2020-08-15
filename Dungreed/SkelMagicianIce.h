#pragma once
#include "Enemy.h"

class SkelMagicianIce : public Enemy
{
private:
	tagShootingInfo _shooting;	// 탄막
	tagAttackInfo	_attack;	// 공격

	Image*			_attackImg;	// 공격 이펙트 이미지
	Animation*		_attackAni;	// 공격 이펙트 프레임
	Vector2			_attackPos;	// 공격 이펙트 좌표 저장용

	bool			_attacking;	// 현재 공격 이펙트 진행 중

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);

	void attackEffect();	
};

