#pragma once
#include "NormalProjectile.h"

class Shooting
{
private:
	string				_bulletName;
	string				_effectName;
	Vector2				_effectSize;
	NormalProjectile*	_bullet;

	float				_delay;
	float				_count;
	float				_angle;
	float				_range;
	float				_speed;

	bool				_isAni;
	bool				_isAniLoop;
	int					_fps;

public:
	void init(string bulletName, string effectName, Vector2 effectSize, float delay, float range, float speed, bool isAni = 0, bool aniLoop = 0, int fps = 0);
	void release();

	bool update(float const timeElapsed);

	void fire(const Vector2& pos, float angle);

	Projectile* getBullet() { return _bullet; }
};

