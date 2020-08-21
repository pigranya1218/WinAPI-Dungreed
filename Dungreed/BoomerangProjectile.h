#pragma once
#include "Projectile.h"

class BoomerangProjectile :	public Projectile
{
private:
	float		_angleRadian;		// 투사체 날라가는 각도
	float		_speed;				// 투사체 날라가는 속도
	
	float		_radius;			// 충돌용

	float		_range;				// 투사체 사정거리
	float		_maxTime;
	float		_count;
	float       _returnCount;
	Vector2		_startPos;			// 투사체 시작위치
	Vector2		_returnPos;
	Image*		_img;				// 투사체 이미지

	bool		_useAni;			// 애니메이션 사용하는가
	Animation*	_ani;				// 투사체 애니메이션

	bool		_checkCollision;	// 스테이지 벽과 충돌 검사를 하는가
	string		_collisionEffect;	// 부딪혀서 폭발할 때 이펙트
	Vector2		_effectSize;		// 부딪혀서 폭발할 때 이펙트 사이즈

	bool _useRotate;				// 투사체를 돌릴 것인가
	bool _ProjectileReturn;

	Image*		_effectImg;			// 이펙트 이미지

	bool		_collsionGround;	// 빨간 선 충돌 여부
	bool		_collisionPlatForm;	// 푸른 선 충돌 여부
	bool		_useGravity;		// 중력 사용 여부
	Vector2		_gravity;			// 중력값

	float		_length;			// 이펙트 길이 조절용 이미지 길이

public:
	BoomerangProjectile() {}
	BoomerangProjectile(const BoomerangProjectile& source);
	void init(string imgKey, float angleRadian, float speed, bool useAni, bool isAniLoop, int aniFps, bool checkCollision, string collisionEffect, Vector2 effectSize, float range, bool useRotate = 1);
	virtual void release();
	virtual void update(float elapsedTime);
	virtual void render();

	// 애니메이션 업데이트 하려고 만듬 삭제하세욥
	virtual void aniUpdate(float const elapsedTime);
	float getRadius() { return _radius; }
	bool getReturn() { return _ProjectileReturn; }
};

