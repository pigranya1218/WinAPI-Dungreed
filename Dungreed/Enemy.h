#pragma once
#include "GameObject.h"

enum class ENEMY_STATE : unsigned int
{
	IDLE,
	MOVE,
	ATTACK,
	SKILL,
	DIE
};

class Enemy : public GameObject
{
protected:
	bool		_isDetect;				// 플레이어 감지 변수 >> 감지하면 공격 시작
	Image*		_img;
	ENEMY_STATE _state;
	Animation*	_ani;

	float _moveAngle;
	float _moveSpeed;

	struct tagAttackInfo	// 공격 관련 변수들
	{
		FloatRect _rect;	// 근접 공격 시 렉트
		float _delay;		// 공격 주기
		float _count;		// 공격 주기 계산용
		float _angle;		// 탄막 사용시 각도

		bool update(float elapseTime)
		{
			_count += elapseTime;

			if (_count >= _delay)
			{
				_count -= _delay;
				return true;
			}
			return false;
		}
	};

	Synthesize(float, _currentHp, currentHp);
	Synthesize(float, _maxHp, maxHp);

public:
	Enemy() {}
	~Enemy() {}

	virtual void init(const Vector2& pos, DIRECTION direction);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setState(ENEMY_STATE state) {}
};

