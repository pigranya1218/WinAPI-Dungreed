#include "stdafx.h"
#include "BulletManager.h"

HRESULT BulletManager::init()
{
	_vBullet.clear();

	return S_OK;
}

void BulletManager::release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].release();
	}
	_vBullet.clear();
}

void BulletManager::update()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].update();
	}
}

void BulletManager::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].render();
	}
}

void BulletManager::createBullet(string imageName, const Vector2& pos, float speed, float angle, float range)
{
	Bullet bullet;

	bullet.init(imageName, pos, angle, speed, range);


	_vBullet.push_back(bullet);
}

void BulletManager::fireBullet()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].setFire(true);
	}
}
