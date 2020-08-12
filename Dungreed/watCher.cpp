#include "watCher.h"

void watCher::init()
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
	_img = IMAGE_MANAGER->findImage("Watcher0");
	_ani1 = new Animation;
	_ani1->start();
	setitem = false;

	//厩技辑府 啊拜
	_price = 600;
}

void watCher::release()
{

}

void watCher::update(Player * player, float const elapsedTime)
{
	if (KEY_MANAGER->isOnceKeyDown('5'))
	{
		setitem = false;
		
	}
	if (KEY_MANAGER->isOnceKeyDown('6'))
	{
		setitem = true;
		
	}
	
	if (!setitem)
	{
		radius = 100;
		_img = IMAGE_MANAGER->findImage("Watcher0");
		_angle -= 0.043f;
		fspeed = 5;
	}
	else
	{
		radius = 130;
		_img = IMAGE_MANAGER->findImage("Watcher1");
		_angle -= 0.062f;
		fspeed = 10;
	}

	_ani1->frameUpdate(elapsedTime);
	_ani1->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani1->setFPS(fspeed);
	_ani1->setPlayFrame(0, _img->getMaxFrameX(), false, true);
	
}

void watCher::backRender(Player * player)
{
	x = cosf(_angle) * radius;
	y = -sinf(_angle) * radius;
	
	Vector2 renderPos = player->getPosition();
	renderPos.x = renderPos.x + x+2;
	renderPos.y = renderPos.y + y-22;	
	_img->setScale(4);
	_img->aniRender(Vector2(renderPos), _ani1, false);
}

void watCher::frontRender(Player * player)

{
}

void watCher::displayInfo()
{
}

void watCher::attack(Player * player)
{
}

void watCher::attack(FloatRect * rect, tagAttackInfo * info)
{
}

void watCher::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void watCher::attack(Projectile * projectile, tagAttackInfo * info)
{
}

void watCher::getHit(Vector2 const position)
{
}

PlayerStat watCher::equip()
{
	return PlayerStat();
}
