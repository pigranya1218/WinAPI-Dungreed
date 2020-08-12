#pragma once
#include "Projectile.h"

// 일직선으로 나아가는 투사체류
class NormalProjectile : public Projectile
{
private:
	float _angleRadian;			// 투사체 날라가는 각도
	float _speed;				// 투사체 날라가는 속도
	
	Image* _img;				// 투사체 이미지

	bool _useAni;				// 애니메이션 사용하는가
	Animation* _ani;			// 투사체 애니메이션

	bool _checkCollision;			// 스테이지 벽과 충돌 검사를 하는가
	string _collisionEffect;	// 부딪혀서 폭발할 때 이펙트
	Vector2 _effectSize;		// 부딪혀서 폭발할 때 이펙트 사이즈

public:
	void init(string imgKey, float angleRadian, float speed, bool useAni, bool isAniLoop, int aniFps, bool isCollision, string collisionEffect, Vector2 effectSize);
	virtual void release();
	virtual void update(float elapsedTime);
	virtual void render();
};

