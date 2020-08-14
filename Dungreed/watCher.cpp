#include "watCher.h"

void watCher::init()
{
	//厩技辑府 鸥涝
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::RARE;	
	_iconImg = IMAGE_MANAGER->findImage("Watcher");
	
	//厩技辑府 可记
	_addStat.evasion = 5;

	radius = 0;
	fspeed = 0;
	anglePos.x = anglePos.y =0;
	_img = IMAGE_MANAGER->findImage("Watcher0");	
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(7);
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
		
	}
	else
	{
		radius = 130;
		_img = IMAGE_MANAGER->findImage("Watcher1");
		_angle -= 0.062f;
		
	}

	_ani->frameUpdate(elapsedTime);
	anglePos.x = cosf(_angle) * radius;
	anglePos.y = -sinf(_angle) * radius;
	
}

void watCher::backRender(Player * player)
{
	
	
	renderPos = player->getPosition();
	renderPos.x = renderPos.x + anglePos.x + 2;
	renderPos.y = renderPos.y + anglePos.y - 22;	
	Vector2 size = Vector2(_img->getFrameSize().x * 2, _img->getFrameSize().y * 2);
	_crash = rectMakePivot(Vector2(renderPos.x, renderPos.y + 25), size, PIVOT::CENTER);
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_crash));


	_img->setScale(4);	
	_img->aniRender(CAMERA->getRelativeV2(Vector2(_crash.left,_crash.top)), _ani, false);
	
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
