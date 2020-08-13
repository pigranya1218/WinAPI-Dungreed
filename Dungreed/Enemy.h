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

	struct tagShootingInfo
	{
		vector<NormalProjectile*> bullets;	// 한 번에 여러개 만들어 놓고 쏘기 위해

		string				bulletName;	// 불렛 이미지 이름
		string				effectName;	// 불렛 이펙트 이름
		Vector2				effectSize;	// 불렛 이펙트 사이즈

		float				delay;		// 딜레이
		float				count;		// 카운트
		float				angle;		// 각도
		float				range;		// 사정거리
		float				speed;		// 스피드

		bool				isAni;		// 애니메이션 사용여부
		bool				aniLoop;	// 애니메이션 루프여부
		bool				isCollision;// 충돌 여부

		unsigned			bulletNum;	// 불렛을 몇개 생성했는지

	public:
		void init(string bulletName, string effectName, float scale, float delay, float range, float speed, bool isCollision = 1, bool isAni = 0, bool aniLoop = 0)
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
			this->range = range;
			this->speed = speed;

			this->isAni = isAni;
			this->aniLoop = aniLoop;
			this->isCollision = isCollision;
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
		void createBullet(const Vector2& pos, float angle)
		{
			this->angle = angle;

			NormalProjectile* bullet = new NormalProjectile;

			bullet->setPosition(pos);
			bullet->setSize(effectSize);
			bullet->setTeam(OBJECT_TEAM::ENEMY);

			bullet->init(bulletName, angle, this->speed, isAni, aniLoop, 10, isCollision, effectName, effectSize);

			bulletNum++;
			bullets.push_back(bullet);
		}
		void fireBullet(EnemyManager* enemyManager);
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
		float speed;
		float angle;
		float gravity;
		float jumpPower;

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
	virtual void init(const Vector2& pos, DIRECTION direction) = 0;
	virtual void release() = 0;
	virtual void update(float const timeElapsed) = 0;
	virtual void render() = 0;

	virtual void setState(ENEMY_STATE state) = 0;

	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }

	void setDetectRange(float const range) { _detectRange = range; }
};

