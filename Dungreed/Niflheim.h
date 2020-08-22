#pragma once
#include "Enemy.h"

#define PILLAMAX 4

enum tagAttackMod
{
	PROTECT,
	SQUARE,
	CYCLONE,
	LINE,
	ARROW,
	ICECLE,
	SPEAR
};

enum tagPhase
{
	FIRST,
	SECOND,
	LAST
};

enum tagState
{
	ENTER,
	IDLE,
	ATTACK,
	STURN,
	DIE
};

struct tagPillarInfo
{
	float angle;
	Vector2 position;
	Vector2 force;
	Image* img;
	Animation* ani;
	//friend class Niflheim;
};


class Niflheim : public Enemy
{
private:

	tagPillarInfo _pillar[4];
	tagPhase _phase;
	tagState _State;
	tagAttackMod _pillaMod;
	tagShootingInfo _shooting;
	float _move_x;
	float _move_y;
	int _count;
	float _boost;

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(tagState state);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);
};



