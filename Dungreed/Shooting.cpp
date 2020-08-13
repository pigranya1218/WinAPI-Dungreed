#include "stdafx.h"
#include "Shooting.h"

void Shooting::init(string bulletName, string effectName, Vector2 effectSize, float delay, float range, float speed, bool isAni, bool aniLoop, int fps)
{
	_bulletName = bulletName;
	_effectName = effectName;
	_effectSize = effectSize;

	_delay = delay;
	_range = range;
	_speed = speed;

	_isAni = isAni;
	_isAniLoop = aniLoop;
	_fps = fps;
}

void Shooting::release()
{
	_bullet->release();
}

bool Shooting::update(float const timeElapsed)
{
	_count += timeElapsed;

	if (_count >= _delay)
	{
		_count -= _delay;

		return true;
	}
	return false;
}

void Shooting::fire(const Vector2& pos, float angle)
{
	_bullet = new NormalProjectile;

	_angle = angle;

	//_bullet->init(_bulletName, _angle, _speed, _isAni, _isAniLoop, _fps, false, "", Vector2(0, 0));
	_bullet->setPosition(Vector2(WINSIZEX/2, WINSIZEY/2));
	_bullet->setSize(_effectSize);
	_bullet->setTeam(OBJECT_TEAM::ENEMY);
	_bullet->init(_bulletName, _angle, _speed, _isAni, _isAniLoop, _fps, false, "", Vector2(0, 0));
}
