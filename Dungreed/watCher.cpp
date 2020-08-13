#include "watCher.h"

void watCher::init()
{
	//厩技辑府 鸥涝
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::RARE;
	

	//厩技辑府 可记
	_addStat.evasion = 5;

	radius = 0;
	fspeed = 0;
	x = y = 0;
	_iconImg = nullptr;
	_img = IMAGE_MANAGER->findImage("Watcher0");
	_ani = new Animation;
	_ani->start();
	setitem = false;



	//厩技辑府 啊拜
	_price = 1200;
}

void watCher::release()
{

}

void watCher::update(Player * player, float const elapsedTime)
{
	if (KEY_MANAGER->isOnceKeyDown('8'))
	{
		setitem = false;
		
	}
	if (KEY_MANAGER->isOnceKeyDown('9'))
	{
		setitem = true;
		
	}
	
	if (!setitem)
	{
		radius = 85;
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

	_ani->frameUpdate(elapsedTime);
	_ani->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(fspeed);
	_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
	
}

void watCher::backRender(Player * player)
{
	x = cosf(_angle) * radius;
	y = -sinf(_angle) * radius;
	
	Vector2 renderPos = player->getPosition();
	renderPos.x = renderPos.x + x+2;
	renderPos.y = renderPos.y + y-22;	
	_img->setScale(4);
	_img->aniRender(Vector2(renderPos), _ani, false);
	Vector2 size = Vector2(_img->getFrameSize().x * 2, _img->getFrameSize().y *2);
	_crash = rectMakePivot(Vector2(renderPos.x, renderPos.y + 25), size, PIVOT::CENTER);
	D2D_RENDERER->drawRectangle(_crash);
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

void watCher::attack(FloatRect * rect, AttackInfo * info)
{
}

void watCher::attack(FloatCircle * circle, AttackInfo * info)
{
}

void watCher::attack(Projectile * projectile, AttackInfo * info)
{
}

void watCher::getHit(Vector2 const position)
{
}

PlayerStat watCher::equip()
{
	return PlayerStat();
}
