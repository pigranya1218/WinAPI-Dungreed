#pragma once
#include "Enemy.h"

#define HANDSPEED 600

class Belial : public Enemy
{
private:
	struct tagHead
	{
		tagMoveInfo _moving;
		tagAttackInfo _attaking;

		Vector2 _moveDir;
		Vector2 _Position;
		Vector2 _size;
		Animation* _Ani;
		ENEMY_STATE	_State;
		FloatRect _Rect;
		Image* _img;

	};
	struct tagHand
	{
		tagMoveInfo _moving;
		tagAttackInfo _attaking;

		Vector2 _moveDir;
		Vector2 _Position;
		Vector2 _size;
		Animation* _Ani;
		ENEMY_STATE	_State;
		FloatRect _Rect;
		Image* _img;

	};
	struct tagSoul
	{
		Vector2 _moveDir;
		tagMoveInfo _moving;
		tagAttackInfo _attaking;

		Vector2 _Position;
		Vector2 _size;
		Animation* _Ani;
		ENEMY_STATE	_State;
		FloatRect _Rect;

		Image* _backimg;
		Image* _particleimg;
	};

	tagHead _head;
	tagHand _rHand;
	tagHand _lHand;
	tagSoul _back;

	Vector2 _moveDir;

	Vector2 _force;
	int _count;


public:

	virtual void init(const Vector2& pos) override;
	void release();
	void update(float const timeElapsed);
	void render();

	void setHeadState(ENEMY_STATE headState);
	void setRHandState(ENEMY_STATE RhandState);
	void setLHandState(ENEMY_STATE LhandState);

	bool playerCollision(const Vector2 & playerPos);
};

