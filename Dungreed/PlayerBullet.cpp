#include "PlayerBullet.h"

void PlayerBullet::init(Vector2 pos, float angle)
{
	_bulletImg = IMAGE_MANAGER->findImage("GunBullet");
	_bulletCount = 1;
	_shootTermTime = 0.1f;
	_reloadTime = 2.5f;
	_position = pos;
	_angle = angle;

	_ani = new Animation;
	_ani->init(_bulletImg->getWidth(), _bulletImg->getHeight(), 4, 1);
	_ani->setDefPlayFrame(false, false);
	_ani->setFPS(1);
	_ani->start();
}

void PlayerBullet::update(float const elapsedTime)
{
	move();
	_ani->frameUpdate(elapsedTime);
}

void PlayerBullet::release()
{
}

void PlayerBullet::render()
{
	_bulletImg->setAngle(_angle);
	_bulletImg->setScale(4);
	_bulletImg->aniRender(_position, _ani);
	//D2D_RENDERER->drawRectangle(_bulletRect);
}

void PlayerBullet::fire()
{

}

void PlayerBullet::move()
{
	_position.x += cosf(_angle);
	_position.y += -sinf(_angle);
}
