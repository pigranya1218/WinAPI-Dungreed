#include "ItemBullet.h"
#include "ProjectileManager.h"


void ItemBullet::init(int itemType, Vector2 pos)
{
	switch (itemType)
	{
		//È­½ÂÃÑ
		case 0:
		{
			_team = OBJECT_TEAM::PLAYER;
			_img = IMAGE_MANAGER->findImage("GunBullet");
			_bulletCount = 1;
			_shootTermTime = 0.1f;
			_reloadTime = 2.5f;
			Vector2 _size = _img->getSize();
			_position = pos;

			_ani = new Animation;
			_ani->init(_img->getWidth(), _img->getHeight(), 3, 1);
			_ani->setDefPlayFrame(false, false);
			_ani->setFPS(5);
		}
		break;

		//
		case 1:
		{

		}
		break;

		case 2:
		{

		}
		break;

		case 3:
		{

		}
		break;
	}
}

void ItemBullet::release()
{
}

void ItemBullet::update(float timeElapsed)
{
	move();
	_bulletRect = rectMakePivot(_position, _size, PIVOT::CENTER);
}

void ItemBullet::render()
{
	_img->setAngle(_angle);
	_img->setScale(4);
	_img->aniRender(_position, _ani);
	D2D_RENDERER->drawRectangle(_bulletRect);
}

void ItemBullet::fire(Vector2 const pos, float const angle)
{
	_angle = angle;
}

void ItemBullet::move()
{
	_position.x += cosf(_angle);
	_position.y += -sinf(_angle);
}
