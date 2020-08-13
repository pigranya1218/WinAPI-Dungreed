#include "GreenBat.h"

void GreenBat::init()
{
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::NORMAL;	

	_price = 600;


	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	_img = IMAGE_MANAGER->findImage("GreenBatF");
	_ani1 = new Animation;
	_ani1->start();
}

void GreenBat::release()
{
}

void GreenBat::update(Player * player, float const elapsedTime)
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

void GreenBat::backRender(Player * player)
{
	renderPos = player->getPosition();
	if (x > renderPos.x + 10)
	{
		x -= 6;
	}
	else if (x <= renderPos.x )
	{
		x += 6;
	}
	if (y > renderPos.y -70)
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

void GreenBat::frontRender(Player * player)
{
}

void GreenBat::displayInfo()
{
}

void GreenBat::attack(Player * player)
{
}

void GreenBat::attack(FloatRect * rect, AttackInfo * info)
{
}

void GreenBat::attack(FloatCircle * circle, AttackInfo * info)
{
}

void GreenBat::attack(Projectile * projectile, AttackInfo * info)
{
}

void GreenBat::getHit(Vector2 const position)
{
}

PlayerStat GreenBat::equip()
{
	return PlayerStat();
}
