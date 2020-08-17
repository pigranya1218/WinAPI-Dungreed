#pragma once
#include "Enemy.h"

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

public:
	void init(const Vector2& pos, DIRECTION direction);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);
};

