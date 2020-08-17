#pragma once
#include "GameObject.h"
#include "AttackInfo.h"
#include "Shooting.h"
#include "NormalProjectile.h"

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
	EnemyManager*		_enemyManager;	// 에너미 매니저
	ENEMY_STATE			_state;			// 현재 상태
	DIRECTION			_direction;		// 행동
	Image*				_img;			// 이미지
	Animation*			_ani;			// 애니메이션
	string				_imageName;		// 이미지 이름
	bool				_isDetect;		// 플레이어를 감지하였는가
	float				_scale;			// 렉트와 출력에 사용할 스케일
	float				_detectRange;	// 플레이어 감지 거리	

	//Synthesize(float, _curHp, Hp);
	//Synthesize(float, _maxHp, Hp);

	// 탄막 사용 시
	struct tagShootingInfo
	{
		vector<NormalProjectile*> bullets;	// 한 번에 여러개 만들어 놓고 쏘기 위해

		string				bulletName;	// 불렛 이미지 이름
		string				effectName;	// 불렛 이펙트 이름
		Vector2				effectSize;	// 불렛 이펙트 사이즈

		float				delay;		// 딜레이
		float				count;		// 카운트
		float				angle;		// 각도
		float				duration;	// 지속시간
		float				speed;		// 스피드

		bool				isAni;		// 애니메이션 사용여부
		bool				aniLoop;	// 애니메이션 루프여부
		bool				isCollision;// 충돌 여부
		bool				isRotate;	// 이미지 회전 여부
		int					bulletNum;	// 생성할 총알 지정

		void init(string bulletName, string effectName, float scale, float delay, float duration, float speed, bool isRotate, bool isCollision, bool isAni, bool aniLoop)
		{
			this->bulletName = bulletName;
			this->effectName = effectName;	

			if (isAni)
			{
				this->effectSize = IMAGE_MANAGER->findImage(bulletName)->getFrameSize() * scale;
			}
			else
			{
				Vector2 size = IMAGE_MANAGER->findImage(bulletName)->getSize();
				this->effectSize = Vector2(size.x * scale, size.y * scale);
			}

			this->delay = delay;
			this->duration = duration;
			this->speed = speed;

			this->isAni = isAni;
			this->aniLoop = aniLoop;
			this->isCollision = isCollision;
			this->isRotate = isRotate;
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
			bullet->setSize(effectSize);
			bullet->setTeam(OBJECT_TEAM::ENEMY);

			bullet->init(bulletName, angle, speed, isAni, aniLoop, 15, isCollision, effectName, effectSize, duration, isRotate);

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

		void fireBullet(EnemyManager* enemyManager, int fireCount = 0);
	};

	// 공격에 관련된 것들
	struct tagAttackInfo
	{
		float delay;	// 딜레이
		float count;	// 카운트용
		float angle;	// 각도
		float distance;	// 거리

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

	// 이동 관련 변수
	struct tagMoveInfo
	{
		Vector2 force;
		Vector2 gravity;

		float angle;
		float delay;
		float count;

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

public:
	virtual void init() {}
	virtual void init(Vector2 pos) {}
	virtual void init(const Vector2& pos, DIRECTION direction) {}
	virtual void release() {};
	virtual void update(float const timeElapsed) {};
	virtual void render() {};

	virtual void setState(ENEMY_STATE state) {};

	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }

	// EnemyManager에서 체크를 위해 호출
	bool isHit(FloatRect* rc, AttackInfo* info) { return false; }
	bool isHit(FloatCircle* circle, AttackInfo* info) { return false; }
	bool isHit(Projectile* projectile, AttackInfo* info) { return false; }

	// Enemy에서 만약 맞았다면 호출될 가상함수
	virtual bool hitEffect(FloatRect* rc, AttackInfo* info) { return false; }
	virtual bool hitEffect(FloatCircle* circle, AttackInfo* info) { return false; }
	virtual bool hitEffect(Projectile* projectile, AttackInfo* info) { return false; }

	void setDetectRange(float const range) { _detectRange = range; }
};

