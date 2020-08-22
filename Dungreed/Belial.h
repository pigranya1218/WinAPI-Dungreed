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
		tagAttackInfo	laserAtk;		// 레이저 공격

		HAND_STATE	state;	// 현재 손 상태

		vector<FloatRect> laserRect;	// 레이저 출력 벡터

		FloatRect			atkRect;	// 레이저 공격렉트

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
		void update(const float timeElapsed, int enemyType, EnemyManager* enemyManager);
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

	// 검은 따로 구현
	class tagSwordInfo : public GameObject
	{		
	public:
		Image*	img;	// 출력할 이미지
		float	angle;	// 앵글	

		tagTimeInfo chargeEffect;
	};

	struct tagParticleInfo
	{
		Image*		img;
		Animation*	ani[5];
		Vector2		pos[5];
	};

	struct tagDeadParticleInfo : public GameObject
	{
		Image* img;
	};

	tagDeadParticleInfo _deadParticle[6];

	tagParticleInfo _particle;

	Vector2			_playerPos;

	tagMoveInfo		_moving;	// 이동
	tagShootingInfo _shooting;	// 탄막용

	vector<tagSwordInfo*>	_sword;		// 검을 담을 벡터
	unsigned int			_swordNum;	// 현재 검 넘버
	tagAttackInfo			_swordAtk;	// 검 공격 판정용

	Image*		_backImg;	// 후광구 이미지
	Animation*	_backAni;	// 후광구 애니메이션
	bool	_backMove;		// 후광구 좌표 이동 플래그

	tagHandInfo _handR;		// 오른손
	tagHandInfo _handL;		// 왼손
	int			_laserNum;	// 레이저 발사 횟수 지정

	tagTimeInfo _attackCycle;	// 공격 주기 저장용

	tagTimeInfo _dieEffect;
	int			_effectNum;

	BELIAL_PHASE _phase;	// 공격 패턴

	bool		_realDead;	// 죽었을 경우 파편이 떨어지는 상태
	float		_deadAngle;	// 머리가 땅에 착지하면 약간 흔들리는 용
	bool		_angleWay;	// 머리가 회전되는 방향

public:
	void init(const Vector2& pos);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
	void setPhase(BELIAL_PHASE phase);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);

	void headMove(const float timeElapsed);
};


