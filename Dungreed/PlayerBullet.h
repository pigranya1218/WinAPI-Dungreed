#pragma once
#include "stdafx.h"

class PlayerBullet
{
private:
	int _bulletCount;
	int _reloadCoolTime;
public:
	PlayerBullet(int type, DIRECTION dir);

	void spawnBullet();
	void reload();
	void shoot();

};

