#pragma once
#include "Enemy.h"



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

	int _maxHp;
	int _HP;



public:

	void init(const Vector2& pos);
	void release();
	void update(float const timeElapsed);
	void render();

	void setHeadState(ENEMY_STATE headState);
	void setRHandState(ENEMY_STATE RhandState);
	void setLHandState(ENEMY_STATE LhandState);

	bool playerCollision(const Vector2 & playerPos);
};

