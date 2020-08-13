#include "Voluspa.h"
#include "stdafx.h"

void Voluspa::init()
{

	//厩技辑府 鸥涝
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::HIGH;
	_img = IMAGE_MANAGER->findImage("Voluspa0");
	_iconImg = IMAGE_MANAGER->findImage("Voluspa");
	//厩技辑府 可记


	//厩技辑府 啊拜
	_price = 4300;

	location.x = 0;
	location.y = 0;
	renderPos.x = -300;
	renderPos.y = WINSIZEY/2;
	Opposition = false;
}

void Voluspa::release()
{
}

void Voluspa::update(Player * player, float const elapsedTime)
{
	location.x = 10;
	

	if (renderPos.x > WINSIZEX)
	{
		Opposition = true;
	}
	else if (renderPos.x < 0)
	{
		Opposition = false;
	}

	

}

void Voluspa::backRender(Player * player)
{

	_img->setScale(4);	
	_img->render(renderPos, false);
}

void Voluspa::frontRender(Player * player)
{
}

void Voluspa::displayInfo()
{
}

void Voluspa::attack(Player * player)
{
}

void Voluspa::attack(FloatRect * rect, AttackInfo * info)
{
}

void Voluspa::attack(FloatCircle * circle, AttackInfo * info)
{
}

void Voluspa::attack(Projectile * projectile, AttackInfo * info)
{
}

void Voluspa::getHit(Vector2 const position)
{
}

PlayerStat Voluspa::equip()
{
	return PlayerStat();
}
