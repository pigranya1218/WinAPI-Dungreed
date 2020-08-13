#include "Voluspa.h"
#include "stdafx.h"

void Voluspa::init()
{

	//악세서리 타입
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::HIGH;
	_img = IMAGE_MANAGER->findImage("Voluspa0");
	_iconImg = IMAGE_MANAGER->findImage("Voluspa");
	//악세서리 옵션


	//악세서리 가격
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
	

	location.x = 45;	

	if (_currAttackDelay > 0) // 공격 딜레이 대기 중
	{
		_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
	}
	
	if (renderPos.x > WINSIZEX+200 )
	{
		
		renderPos.y = _ptMouse.y;	
		if (_currAttackDelay == 0 ) {
			_currAttackDelay = 3.1f;
			Opposition = true;
		}
	}
	if (renderPos.x < -200 )
	{
		
		renderPos.y = _ptMouse.y;	
		if (_currAttackDelay == 0 ) {
			_currAttackDelay = 2.9f;
			Opposition = false;
		}
	}
	if (Opposition)
	{
		renderPos.x -= location.x;
	}
	else
	{
		renderPos.x += location.x;
	}
	

}

void Voluspa::backRender(Player * player)
{

	_img->setScale(3);	
	if (Opposition)
	{
		_img->render(renderPos, true);
	}
	else
	{
		_img->render(renderPos, false);
	}

	
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
