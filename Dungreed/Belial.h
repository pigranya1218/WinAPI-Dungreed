#pragma once
#include "Enemy.h"

#define HANDSPEED 600
#define PARTICLEMAX 30
#define SIZEMAX 5

enum class BELIAL_PHASE : unsigned
{
	SHOOTING_READY,	// 탄막 준비
	SHOOTING,		// 탄막 공격
	SHOOTING_FINAL,	// 탄막 마무리
	SWORD_READY,	// 검 준비
	SWORD,			// 검 공격
	SWORD_FINAL,	// 검 마무리
	LASER_READY,	// 레이저 준비
	LASER,			// 레이저 발사
	LASER_FINAL		// 레이저 마무리
};

class Belial : public Enemy
{
private:	
	struct tagHandInfo
	{

	};

	// 단순히 시간 계산용
	struct tagTimeInfo
	{
		float delay;
		float count;

		bool update(const float timeElapsed)
		{
			count += timeElapsed;
			if (count >= delay)
			{
				count = 0;
				return true;
			}
			return false;
		}
	};

	struct tagSwordPosAngle
	{		
		Vector2 pos;	// 포지션
		float angle;	// 앵글
	};

	tagMoveInfo		_moving;		// 이동
	tagShootingInfo _shooting;		// 탄막용
	tagShootingInfo _swordBullet;	// 검 던지기 패턴

	Image*						_swordImg;		// 검 이미지
	vector<tagSwordPosAngle>	_swordPosAngle;	// 검 출력용

	Image*		_backImg;		// 후광구 이미지
	Animation*	_backAni;		// 후광구 애니메이션

	tagHandInfo _handR;			// 오른손
	tagHandInfo _handL;			// 왼손

	tagTimeInfo _attackCycle;	// 공격 주기 저장용

	BELIAL_PHASE _phase;		// 공격 패턴

public:
	void init(const Vector2& pos);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
	void setPhase(BELIAL_PHASE phase);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);
};


