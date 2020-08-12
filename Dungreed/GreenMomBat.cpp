#include "GreenMomBat.h"
#include "stdafx.h"

void GreenMomBat::init()
{
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::NORMAL;
	//_img = IMAGE_MANAGER->findImage("babyGreenBat");

	_price = 600;


	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	_img = IMAGE_MANAGER->findImage("GreenMomBatF");
	_ani1 = new Animation;
	_ani1->start();
}

void GreenMomBat::release()
{
}

void GreenMomBat::update(Player * player, float const elapsedTime)
{
	if (_ptMouse.x < renderPos.x)
	{
		_direction = DIRECTION::LEFT;

	}
	else
	{
		_direction = DIRECTION::RIGHT;

	}
	_ani1->frameUpdate(elapsedTime);
	_ani1->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani1->setFPS(11);
	_ani1->setPlayFrame(0, _img->getMaxFrameX(), false, true);
}

void GreenMomBat::backRender(Player * player)
{
	renderPos = player->getPosition();
	if (x > renderPos.x + 80)
	{
		x -= 6;
	}
	else if (x <= renderPos.x+60)
	{
		x += 6;
	}
	if (y > renderPos.y - 70)
	{
		y -= 7;
	}
	else if (y < renderPos.y - 80 && y <= renderPos.y)
	{
		y += 8;
	}
	_img->setScale(4);
	_img->aniRender(Vector2(x, y), _ani1, _direction == DIRECTION::LEFT);
}

void GreenMomBat::frontRender(Player * player)
{
}

void GreenMomBat::displayInfo()
{
}

void GreenMomBat::attack(Player * player)
{
}

void GreenMomBat::attack(FloatRect * rect, tagAttackInfo * info)
{
}

void GreenMomBat::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void GreenMomBat::attack(Projectile * projectile, tagAttackInfo * info)
{
}

void GreenMomBat::getHit(Vector2 const position)
{
}

PlayerStat GreenMomBat::equip()
{
	return PlayerStat();
}
