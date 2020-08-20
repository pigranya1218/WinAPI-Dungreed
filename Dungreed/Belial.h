#pragma once
#include "Enemy.h"

#define HANDSPEED 600
#define PARTICLEMAX 30
#define SIZEMAX 5

enum class BELIAL_STATE : int
{
	SHOOTING,
	SWORD,
	LASER
};

class Belial : public Enemy
{
private:
	tagMoveInfo _moving;
	tagShootingInfo _shooting;

	struct tagHandInfo
	{

	};

	tagHandInfo _handR;
	tagHandInfo _handL;

public:
	void init(const Vector2& pos);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
};

