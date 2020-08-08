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
	bool _isDetect;				// 플레이어 감지 변수 >> 감지하면 공격 시작
	Image* _img;
	

	Synthesize(float, _currentHp, currentHp);
	Synthesize(float, _maxHp, maxHp);

public:
	Enemy() {}
	~Enemy() {}

	virtual void init(Vector2 pos, DIRECTION direction);
	virtual void release();
	virtual void update();
	virtual void render();
};

