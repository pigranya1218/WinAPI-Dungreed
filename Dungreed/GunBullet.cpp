#include "GunBullet.h"
//#include "ProjectileManager.h"


void GunBullet::init(Vector2 pos)
{
	_team = OBJECT_TEAM::PLAYER;
	_img = IMAGE_MANAGER->findImage("GunBullet");
	_bulletCount = 1;
	_shootTermTime = 0.1f;
	_reloadTime = 2.5f;
	Vector2 _size = Vector2(_img->getSize().x, _img->getSize().y);
	_position = pos;

	_ani = new Animation;
	_ani->init(_img->getFrameSize().x, _img->getFrameSize().y, 3, 1);
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(5);
}

void GunBullet::release()
{
}

void GunBullet::update(float timeElapsed)
{
	move();
}

void GunBullet::render()
{
	_img->setAngle(_angle);
	_img->setScale(4);
	_img->aniRender(_position, _ani);
	//D2D_RENDERER->drawRectangle(_bulletRect);
}

void GunBullet::fire(Vector2 const pos, float const angle, int itemType)
{
	_angle = angle;
	//_bulletRect = rectMakePivot(_position, _size, PIVOT::CENTER);
	//GunBullet* _bullet = new GunBullet;
	//_bullet->init(itemType, pos);
}

void GunBullet::move()
{
	_position.x += cosf(_angle);
	_position.y += -sinf(_angle);
}
