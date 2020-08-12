#include "GreenDadBat.h"
#include "stdafx.h"

void GreenDadBat::init()
{
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::NORMAL;


	_price = 600;


	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	_img = IMAGE_MANAGER->findImage("GreenDadBatF");
	_ani1 = new Animation;
	_ani1->start();
}

void GreenDadBat::release()
{
}

void GreenDadBat::update(Player * player, float const elapsedTime)
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
	_ani1->setFPS(10);
	_ani1->setPlayFrame(0, _img->getMaxFrameX(), false, true);
}

void GreenDadBat::backRender(Player * player)
{
	renderPos = player->getPosition();
	if (x > renderPos.x - 70)
	{
		x -= 6;
	}
	else if (x <= renderPos.x -90)
	{
		x += 6;
	}
	if (y > renderPos.y + 5 && y > renderPos.y)
	{
		y -= 7;
	}
	else if (y < renderPos.y - 5 )
	{
		y += 8;
	}
	_img->setScale(4);
	_img->aniRender(Vector2(x, y), _ani1, _direction == DIRECTION::LEFT);
}

void GreenDadBat::frontRender(Player * player)
{
}

void GreenDadBat::displayInfo()
{
}

void GreenDadBat::attack(Player * player)
{
}

void GreenDadBat::attack(FloatRect * rect, tagAttackInfo * info)
{
}

void GreenDadBat::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void GreenDadBat::attack(Projectile * projectile, tagAttackInfo * info)
{
}

void GreenDadBat::getHit(Vector2 const position)
{
}

PlayerStat GreenDadBat::equip()
{
	return PlayerStat();
}
