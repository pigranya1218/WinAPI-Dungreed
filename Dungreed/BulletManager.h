#pragma once
#include "Bullet.h"

class BulletManager
{
private:
	vector<Bullet> _vBullet;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	void createBullet(string imageName, const Vector2& pos, float speed, float angle, float range, float scale = 1.0f);
	void fireBullet();

	auto getBullet() { return _vBullet; }
};

