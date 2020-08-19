#pragma once
#include "Enemy.h"
#include <vector>
#define HANDSPEED 600
#define PARTICLEMAX 30
#define SIZEMAX 5

class Belial : public Enemy
{
private:
	struct tagHead
	{
		tagMoveInfo _moving;
		tagAttackInfo _attack;

		tagShootingInfo _shooting;

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
		Animation* _lAni;

		ENEMY_STATE	_State;
		FloatRect _Rect;
		Image* _img;
		Image* _laserImg;
		Image* _laserHeadImg;
	};
	struct tagSoul
	{
		Vector2 _moveDir;
		tagMoveInfo _moving;
		tagAttackInfo _attaking;

		Vector2 _Position;
		Vector2 _size;
		Animation* _Ani;
		Animation* _pAni;
		Animation* _pAni2;
		Animation* _pAni3;
		Animation* _pAni4;

		ENEMY_STATE	_State;
		FloatRect _Rect;

		Image* _backimg;
		Image* _particleimg;
	};
	struct tagTheSword
	{
		tagMoveInfo _moving;
		tagAttackInfo _attaking;
		tagShootingInfo _shooting;

		Vector2 _moveDir;
		Vector2 _Position;
		Vector2 _size;
		Animation* _Ani;
		ENEMY_STATE	_State;
		FloatRect _Rect;
		Image* _img;
	};

	tagHead _head;
	tagHand _rHand;
	tagHand _lHand;
	tagSoul _back;
	tagTheSword _sword;

	Vector2 _moveDir;

	Vector2 _force;
	int _count;

	int _particleMove_x[PARTICLEMAX];
	int _particleMove_y[PARTICLEMAX];
	int _particleSize;
	int _particleSize2;
	int _particleSize3;

	float _angle;

public:


	vector<tagTheSword> _vSword;

	void init(const Vector2& pos);
	void release();
	void update(float const timeElapsed);
	void render();

	void setHeadState(ENEMY_STATE headState);
	void setRHandState(ENEMY_STATE RhandState);
	void setLHandState(ENEMY_STATE LhandState);



	bool playerCollision(const Vector2 & playerPos);
};

