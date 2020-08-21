#pragma once
#include "GameObject.h"
#include "AttackInfo.h"
#include "Shooting.h"
#include "NormalProjectile.h"


#define MAXHP 150
class EnemyManager;

enum class ENEMY_STATE
{
	IDLE,		// 기본
	MOVE,		// 이동
	ATTACK,		// 공격
	SKILL,		// 특수
	DIE			// 죽음
};

// 탄막 공격 용


class Enemy : public GameObject
{
protected:
	EnemyManager*	_enemyManager;	// 에너미 매니저
	ENEMY_STATE		_state;			// 현재 상태
	DIRECTION		_direction;		// 행동
	Image*			_img;			// 이미지
	Sound*			_sound;			// 사운드
	Animation*		_ani;			// 애니메이션
	string			_imageName;		// 이미지 이름
	string			_soundName;		// 사운드 이름	

	bool			_isDetect;		// 플레이어를 감지하였는가
	float			_scale;			// 렉트와 출력에 사용할 스케일
	float			_detectRange;	// 플레이어 감지 거리	

	float			_curHp;
	float			_maxHp;

	int				_myEnemyType;	// 에너미 타입 변수

	vector<size_t>		_attackedId; // 최근 공격받았던 공격들의 아이디 값들을 저장하는 벡터, 최대 10칸 정도 저장하면 적당할 듯

	// 탄막 공격 사용 시
	struct tagShootingInfo
	{
		vector<NormalProjectile*> bullets;	// 한 번에 여러개 만들어 놓고 쏘기 위해

		AttackInfo info;			// 공격 정보 저장용

		string	bulletName;			// 불렛 이미지 이름
		string	effectName;			// 불렛 이펙트 이름

		Vector2	effectSize;			// 불렛 이펙트 사이즈
		Vector2 drawSize;			// 그릴 사이즈
		Vector2 collisionSize;		// 충돌 사이즈
		Vector2	force;				// 불렛 날아가는 힘

		float	delay;				// 딜레이
		float	count;				// 카운트
		float	angle;				// 각도
		float	duration;			// 지속시간

		bool	collisionGround;	// 붉은 선 충돌여부
		bool	collisionPlatForm;	// 푸른 선 충돌여부
		bool	isAni;				// 애니메이션 사용여부
		bool	aniLoop;			// 애니메이션 루프여부
		bool	isRotate;			// 이미지 회전 여부
		bool	isGravity;			// 중력 사용 여부

		int		bulletNum;			// 생성할 총알 지정

		// 총알 초기화 >> 불렛 이미지이름, 이펙트 이름, 투사체 날아가는 힘, 스케일, 투사체 발사주기, 투사체 지속시간, 이미지 회전여부, 프레임 사용여부, 프레임 루프여부, 중력 적용여부, 붉은 선 충돌여부, 푸른 선 충돌여부
		void init(string bulletName, string effectName, Vector2 force, float scale, float delay, float duration, bool isRotate = 0, bool isAni = 1, bool aniLoop = 1, bool isGravity = 0, bool collisionGround = 1, bool collisionPlatForm = 1)
		{
			this->bulletName = bulletName;
			this->effectName = effectName;	

			if (isAni)
			{
				collisionSize = drawSize = IMAGE_MANAGER->findImage(bulletName)->getFrameSize() * scale;
			}
			else
			{
				Vector2 size = IMAGE_MANAGER->findImage(bulletName)->getSize();
				collisionSize = drawSize = Vector2(size.x * scale, size.y * scale);
			}

			this->delay = delay;
			this->duration = duration;
			this->force = force;

			this->isAni = isAni;
			this->aniLoop = aniLoop;			
			this->isRotate = isRotate;
			this->isGravity = isGravity;
			this->collisionGround = collisionGround;
			this->collisionPlatForm = collisionPlatForm;
		}		
		void attackInit(const float minDamage, const float maxDamage, const float trueDamage, const float knockBack = 15)
		{
			info.minDamage = minDamage;
			info.maxDamage = maxDamage;
			info.trueDamage = trueDamage;
			info.knockBack = knockBack;
		}
		// 딜레이 업데이트
		bool delayUpdate(float const timeElapsed)
		{
			count += timeElapsed;

			if (count >= delay)
			{
				count = 0;
				return true;
			}
			return false;
		}
		// 총알 생성
		void createBullet(const Vector2& pos, float angle)
		{
			this->angle = angle;

			NormalProjectile* bullet = new NormalProjectile;
			bullet->setPosition(pos);
			//bullet->setSize(effectSize);
			
			bullet->init(bulletName, effectName, drawSize, collisionSize, drawSize, force, duration, angle, isAni, aniLoop, 15, isRotate, isGravity, collisionGround, collisionPlatForm);

			if (bulletNum > 0) --bulletNum;
			bullets.push_back(bullet);
		}
		void aniUpdate(const float timeElapsed)
		{
			for (int i = 0; i < bullets.size(); i++)
			{
				bullets[i]->aniUpdate(timeElapsed);
			}
		}
		// 총알 출력
		void render(int maxNum = -1)
		{
			int loopSize = (maxNum == -1) ? (bullets.size()) : (maxNum);

			for (int i = 0; i < loopSize; i++)
			{
				bullets[i]->render();
			}
		}

		void fireBullet(int enemyCode, EnemyManager* enemyManager, int fireCount = 0);
	};

	// 근접 공격에 관련된 것들
	struct tagAttackInfo
	{
		float		delay;			// 딜레이
		float		count;			// 카운트용
		float		angle;			// 각도
		float		distance;		// 거리
		float		circleSize;		// 공격 판정 사이즈(반지름)

		FloatCircle circleDebug;	// 디버그용
		FloatRect	rectDebug;		// 디버그?
		AttackInfo	info;			// 공격정보

		string id;	// 공격 ID 저장용

		// 공격 쿨타임 업데이트용
		bool update(float const timeElapsed)
		{
			count += timeElapsed;

			if (count >= delay)
			{
				count = 0;
				return true;
			}
			return false;
		}
		// 공격 정보 저장용
		void attackInit(float minDamage, float maxDamage, float trueDamage, float critical = 0, float criDamage = 0, float knockBack = 15)
		{
			info.minDamage = minDamage;
			info.maxDamage = maxDamage;
			info.trueDamage = trueDamage;
			info.critical = critical;
			info.criticalDamage = criDamage;
			info.knockBack = knockBack;

			id.clear();
		}
		// 공격 (원)
		void attackCircle(int enemyCode, EnemyManager* enemyManager, const Vector2& pos, const float startRad, const float endRad);
		// 공격 (렉트)
		void attackRect(int enemyCode, EnemyManager* enemyManager, FloatRect rc);
	};

	// 이동 관련 변수
	struct tagMoveInfo
	{
		Vector2 force;		// 이동할 힘
		Vector2 gravity;	// 이동 저항 변수

		float angle;		// 삼각함수로 움직일 경우 사용
		float delay;		// 딜레이
		float count;		// 카운트

		// 쿨타임 업데이트용
		bool update(float const timeElapsed)
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

	// 피격 관련
	struct tagHitInfo
	{
		bool isHit;		// 피격 판정중인지 확인용

		float delay;
		float count;

		// 피격 판정 쿨타임용
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

	tagHitInfo	_hit;		// 피격 구조체는 모든 에너미가 사용함
	tagMoveInfo	_moving;	// 이동 구조체도 모든 에너미가 사용함

public:
	
	virtual ~Enemy() {}
	virtual void init() {}
	virtual void init(const Vector2& pos) {}
	virtual void init(const Vector2& pos, DIRECTION direction) {}
	virtual void release() = 0;
	virtual void update(float const timeElapsed) = 0;
	virtual void render() = 0;

	// 상태 변환
	virtual void setState(ENEMY_STATE state) {};

	// 피격 후 행동처리
	virtual void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed) {}

	virtual void dieEffect();

	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }

	// 현재체력 접근자 설정자
	void setCurHp(float curHp) { _curHp = curHp; }
	float getCurHp() const { return _curHp; }

	// 최대체력 접근자 설정자
	void setMaxHp(float maxHp) { _maxHp = maxHp; }
	float getMaxHp() const { return _maxHp; }

	// EnemyManager에서 체크를 위해 호출
	bool isHit(FloatRect* rc, AttackInfo* info);
	bool isHit(FloatCircle* circle, AttackInfo* info);
	bool isHit(Projectile* projectile);

	// Enemy에서 만약 맞았다면 호출될 가상함수
	virtual bool hitEffect(FloatRect* rc, AttackInfo* info) { return false; }
	virtual bool hitEffect(FloatCircle* circle, AttackInfo* info);
	virtual bool hitEffect(Projectile* projectile);

	void setDetectRange(float const range) { _detectRange = range; }
};

