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

	for (int i = 0; i < _vBullet.size();)
	{
		if (_vBullet[i].getDelete())
		{
			_vBullet.erase(_vBullet.begin() + i);
			break;
		}
		else
		{
			i++;
		}
	}
}

void BulletManager::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].render();
	}
}

void BulletManager::createBullet(string imageName, const Vector2& pos, float speed, float angle, float range, float scale)
{
	Bullet bullet;

	bullet.init(imageName, pos, angle, speed, range, scale);


	_vBullet.push_back(bullet);
}

void BulletManager::fireBullet()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].setFire(true);
	}
}
