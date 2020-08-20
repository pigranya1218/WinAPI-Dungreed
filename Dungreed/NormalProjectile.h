#pragma once
#include "Projectile.h"

// 일직선으로 나아가는 투사체류
class NormalProjectile : public Projectile
{
private:

	float		_maxTime;			// 투사체 지속시간
	float		_count;				// 시간 계산용

	Image*		_img;				// 투사체 이미지
	Image*		_effectImg;			// 이펙트 이미지
	Vector2		_effectSize;        // 이펙트 사이즈

	bool		_useAni;			// 애니메이션 사용하는가
	Animation*	_ani;				// 투사체 애니메이션

	bool		_collsionGround;	// 빨간 선 충돌 여부
	bool		_collisionPlatForm;	// 푸른 선 충돌 여부

	string		_collisionEffect;	// 부딪혀서 폭발할 때 이펙트
	Vector2		_drawSize;			// 부딪혀서 폭발할 때 이펙트 사이즈

	bool		_useGravity;		// 중력 사용 여부
	Vector2		_gravity;			// 중력값

	bool		_useRotate;			// 투사체를 돌릴 것인가
	

	float		_length;			// 이펙트 길이 조절용 이미지 길이

public:
	//				불렛이미지 키 이름,	이펙트 이름,	렌더 사이즈,	충돌 사이즈,	이펙트 사이즈, 투사체 날아갈 힘, 투사체 지속시간, 각도, 프레임 사용여부, 프레임 루프여부, 프레임속도, 불렛 회전여부,	중력 적용여부, 붉은 선 충돌여부, 푸른 선 충돌여부, 에너미 관통 여부
	void init(const string imgKey, const string collisionEffect, const Vector2& drawSize, const Vector2& collsionRectSize, const Vector2& effectSize, const Vector2& force, const float maxTime, const float angleRadian, bool useAni, bool isAniLoop, int aniFps, bool useRotate = 1, bool useGravity = 0, bool collsionGround = 1, bool collsionPlatForm = 1, bool collsionEnemy = 1);

	virtual void release();
	virtual void update(float elapsedTime);
	virtual void render();

	// 애니메이션 업데이트 하려고 만듬 
	virtual void aniUpdate(float const elapsedTime);
	
};

