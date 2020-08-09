#include "stdafx.h"
#include "Bullet.h"

void Bullet::init(string imageName, const Vector2& pos, float angle, float speed, float range)
{
	_imageName = imageName;
	_img = IMAGE_MANAGER->findImage(imageName);

	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(1);
	_ani->start();

	_position = pos;
	_angle = angle;
	_speed = speed;
	_range = range;

	_rect = rectMakePivot(_position, _img->getFrameSize(), PIVOT::CENTER);

	_active = true;
	_isFire = _isDelete = false;
}

void Bullet::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Bullet::update()
{
	if (_isFire)
	{
		_position.x += cosf(_angle) * (TIME_MANAGER->getElapsedTime() * _speed);
		_position.y -= sinf(_angle) * (TIME_MANAGER->getElapsedTime() * _speed);
	}


	_ani->frameUpdate(TIME_MANAGER->getElapsedTime() * 10);

	_rect = rectMakePivot(_position, _img->getFrameSize(), PIVOT::CENTER);
}

void Bullet::render()
{
	_img->setScale(3.0f);
	_img->aniRender(_rect.getCenter(), _ani, false);
}
