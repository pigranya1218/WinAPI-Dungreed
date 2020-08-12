#include "babyGreenBat.h"

void babyGreenBat::init()
{
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::NORMAL;
	//_img = IMAGE_MANAGER->findImage("babyGreenBat");

	_price = 600;

	
	x = WINSIZEX/2;
	y = WINSIZEY/2;
	_img = IMAGE_MANAGER->findImage("babyGreenBatF");
	_ani1 = new Animation;
	_ani1->start();

}

void babyGreenBat::release()
{
	
}

void babyGreenBat::update(Player* player, float const elapsedTime)
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

void babyGreenBat::frontRender(Player* player)
{
}

void babyGreenBat::backRender(Player* player)
{
	
	renderPos = player->getPosition();
	if (x > renderPos.x + 60)
	{
		x -= 6;
	}
	else if (x <= renderPos.x + 10)
	{
		x += 6;
	}
	if (y > renderPos.y + 5 && y > renderPos.y)
	{
		y -= 7;
	}
	else if (y < renderPos.y - 5 && y <= renderPos.y)
	{
		y += 8;
	}	
	_img->setScale(3);
	_img->aniRender(Vector2(x, y), _ani1, _direction == DIRECTION::LEFT);
}


void babyGreenBat::displayInfo()
{
}

void babyGreenBat::attack(Player* player)
{
	
}

void babyGreenBat::attack(FloatRect * rect, tagAttackInfo * info)
{
	
}

void babyGreenBat::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void babyGreenBat::attack(Projectile * projectile, tagAttackInfo * info)
{
}

void babyGreenBat::getHit(Vector2 const position)
{
}

PlayerStat babyGreenBat::equip()
{
	return PlayerStat();
}
