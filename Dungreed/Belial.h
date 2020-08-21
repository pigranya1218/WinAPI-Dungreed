#pragma once
#include "Enemy.h"

#define HANDSPEED 600
#define PARTICLEMAX 30
#define SIZEMAX 5

enum class BELIAL_PHASE : unsigned
{
	SHOOTING_READY,	// 탄막 준비
	SHOOTING_START,	// 탄막 공격
	SHOOTING_FINAL,	// 탄막 마무리
	SWORD_READY,	// 검 준비
	SWORD_START,	// 검 공격
	SWORD_FINAL,	// 검 마무리
	LASER_R,		// 레이저 우측
	LASER_L,		// 레이저 좌측
};

enum class HAND_STATE : unsigned
{
	IDLE,
	MOVE,
	ATTACK_READY,
	ATTACK_START,
	ATTACK_FINAL
};

class Belial : public Enemy
{
private:	
	struct tagHandInfo
	{
		Image*		img;		// 손 이미지
		Animation*	ani;		// 손 애니메이션
		Vector2		position;	// 손 좌표
		Vector2		movePos;	// 이동해야할 좌표

		Image*		laserHeadImg;	// 레이저 머리
		Image*		laserBodyImg;	// 레이저 중간
		Animation*	laserHeadAni;	// 레이저 머리 애니메이션
		Animation*	laserBodyAni;	// 레이저 중간 애니메이션

		tagMoveInfo moving;	// 이동

		HAND_STATE	state;	// 현재 손 상태

		vector<FloatRect> laserRect;	// 레이저 출력 및 공격 판정용

		// 초기화
		void init(const Vector2& pos);
		// 메모리 해제
		void release()
		{
			ani->release();
			laserHeadAni->release();
			laserBodyAni->release();

			SAFE_DELETE(ani);
			SAFE_DELETE(laserHeadAni);
			SAFE_DELETE(laserBodyAni);
		}
		// 손 업데이트
		void update(const float timeElapsed);
		// 출력
		void render(const float scale, bool bisymmetry = 0);

		void setState(HAND_STATE state, const Vector2& movePos = Vector2(0, 0));
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

	Vector2			_playerPos;

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

	int _laserNum;	// 레이저 발사 횟수 지정

public:
	void init(const Vector2& pos);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
	void setPhase(BELIAL_PHASE phase);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);
};


