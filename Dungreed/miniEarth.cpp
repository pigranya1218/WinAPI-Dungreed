#include "miniEarth.h"
#include "stdafx.h"

void miniEarth::init()
{
	//厩技辑府 鸥涝
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::NORMAL;
	_iconImg = IMAGE_MANAGER->findImage("MiniEarth");
	_img = IMAGE_MANAGER->findImage("MiniEarth0");

	//厩技辑府 可记	

	//厩技辑府 啊拜
	_price = 600;


	_x = _y = 0;
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(20);
	_ani->start();
}

void miniEarth::release()
{
}

void miniEarth::update(Player * player, float const elapsedTime)
{
	_angle += 1.523f*elapsedTime;
	_ani->frameUpdate(elapsedTime);
	_ani->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(10);
	_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
}

void miniEarth::backRender(Player * player)
{
	_x = cosf(_angle) * 55;
	_y = -sinf(_angle) * 55;

	Vector2 renderPos = player->getPosition();
	renderPos.x = renderPos.x + _x;
	renderPos.y = renderPos.y + _y - 20;
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(renderPos), _ani, false);
}

void miniEarth::frontRender(Player * player)
{
}

void miniEarth::displayInfo()
{
}

void miniEarth::attack(Player * player)
{
}

void miniEarth::attack(FloatRect * rect, AttackInfo * info)
{
}

void miniEarth::attack(FloatCircle * circle, AttackInfo * info)
{
}

void miniEarth::attack(Projectile * projectile, AttackInfo * info)
{
}

void miniEarth::getHit(Vector2 const position)
{
}

void miniEarth::equip(Player* player)
{
}
