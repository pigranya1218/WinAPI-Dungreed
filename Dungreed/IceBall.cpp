#include "IceBall.h"
#include "stdafx.h"

void IceBall::init()
{
	//厩技辑府 鸥涝
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::NORMAL;
	
	

	//厩技辑府 可记
	_addStat.criticalChance = 1;
	_addStat.defense = 1;

	radius = 0;
	fspeed = 0;
	x = y = 0;
	_img = IMAGE_MANAGER->findImage("IceBall");
	_ani = new Animation;
	_ani->start();
	setitem = false;
	//厩技辑府 啊拜
	_price = 600;
}

void IceBall::release()
{
}

void IceBall::update(Player * player, float const elapsedTime)
{
	if (KEY_MANAGER->isOnceKeyDown('6'))
	{
		setitem = false;

	}
	if (KEY_MANAGER->isOnceKeyDown('7'))
	{
		setitem = true;

	}

	if (!setitem)
	{
		radius = 65;
		_img = IMAGE_MANAGER->findImage("IceBall");
		_angle -= 0.043f;
		fspeed = 5;
	}
	else
	{
		radius = 85;
		_img = IMAGE_MANAGER->findImage("IceBall0");
		_angle -= 0.062f;
		fspeed = 10;
		_ani->frameUpdate(elapsedTime);
		_ani->init(_img->getWidth(), _img->getHeight(),
			_img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(fspeed);
		_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
	}

	

	
}

void IceBall::backRender(Player * player)
{
	

	x = cosf(_angle) * radius;
	y = -sinf(_angle) * radius;

	Vector2 renderPos = player->getPosition();
	renderPos.x = renderPos.x + x + 5;
	renderPos.y = renderPos.y + y - 20;
	_img->setScale(4);
	if (!setitem)
	{
		_img->render(renderPos, false);
		Vector2 size = Vector2(_img->getFrameSize().x * 4, _img->getFrameSize().y * 4);
		_crash = rectMakePivot(Vector2(renderPos.x, renderPos.y ), size, PIVOT::CENTER);
	}
	else
	{
		_img->aniRender(Vector2(renderPos), _ani, false);
		Vector2 size = Vector2(_img->getFrameSize().x * 2, _img->getFrameSize().y * 2);
		_crash = rectMakePivot(Vector2(renderPos.x-1, renderPos.y + 19), size, PIVOT::CENTER);
	}
	
	D2D_RENDERER->drawRectangle(_crash);
	

	

}

void IceBall::frontRender(Player * player)
{
}

void IceBall::displayInfo()
{
}

void IceBall::attack(Player * player)
{
}

void IceBall::attack(FloatRect * rect, AttackInfo * info)
{
}

void IceBall::attack(FloatCircle * circle, AttackInfo * info)
{
}

void IceBall::attack(Projectile * projectile, AttackInfo * info)
{
}

void IceBall::getHit(Vector2 const position)
{
}

PlayerStat IceBall::equip()
{
	return PlayerStat();
}
