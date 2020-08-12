#pragma once
#include "GameObject.h"

class EnemyManager;

enum class ENEMY_STATE
{
	IDLE,        // 기본
	MOVE,        // 이동
	ATTACK,        // 공격
	SKILL,        // 특수
	DIE            // 죽음
};

class Enemy : public GameObject
{
protected:
	EnemyManager*    _enemyManager;    // 에너미 매니저

	ENEMY_STATE        _state;        // 현재 상태

	DIRECTION        _direction;        // 행동

	Image*            _img;            // 이미지
	Animation*        _ani;            // 애니메이션
	string            _imageName;        // 이미지 이름

	struct tagAttackInfo
	{
		float delay;    // 딜레이
		float count;    // 카운트용
		float angle;    // 각도
		float distance;    // 거리

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

	bool    _isDetect;        // 플레이어를 감지하였는가
	float    _scale;            // 렉트와 출력에 사용할 스케일
	float    _detectRange;    // 플레이어 감지 거리

public:
	void init() {}
	virtual void init(const Vector2& pos, DIRECTION direction) = 0;
	virtual void release() = 0;
	virtual void update(float const timeElapsed) = 0;
	virtual void render() = 0;

	virtual void setState(ENEMY_STATE state) = 0;

	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
};