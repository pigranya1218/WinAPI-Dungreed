#include "Voluspa.h"
#include "stdafx.h"

void Voluspa::init()
{

	//악세서리 타입
	_itemCode = 0x0330C;
	_img = IMAGE_MANAGER->findImage("Voluspa0");
	_iconImg = IMAGE_MANAGER->findImage("Voluspa");
	//악세서리 옵션

	_itemName = L"볼루스파";
	_displayInfos.push_back(L"적을 자동으로 노리는  얼음창 소환");
	_displayText = L"\"그대 아직도 깨달음을 원하는가? 그리고 무엇을 알려는가?\"";
	//악세서리 가격
	_price = 4300;

	_location.x = 0;
	_location.y = 0;
	
	_renderPos.x = -300;
	_renderPos.y = WINSIZEY/2;
	_Opposition = false;
}

void Voluspa::release()
{
}

void Voluspa::update(Player * player, float const elapsedTime)
{
	

	_location.x = 2500* elapsedTime;

	if (_currAttackDelay > 0) // 공격 딜레이 대기 중
	{
		_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
	}
	
	if (_renderPos.x > WINSIZEX+200 )
	{
		
		_renderPos.y = CAMERA->getAbsoluteY(_ptMouse.y);
		if (_currAttackDelay == 0 ) {
			_currAttackDelay = 3.1f;
			_Opposition = true;
		}
	}
	if (_renderPos.x < -200 )
	{
		
		_renderPos.y = CAMERA->getAbsoluteY(_ptMouse.y);
		if (_currAttackDelay == 0 ) {
			_currAttackDelay = 2.9f;
			_Opposition = false;
		}
	}
	if (_Opposition)
	{
		_renderPos.x -= _location.x;
	}
	else
	{
		_renderPos.x += _location.x;
	}
	

}

void Voluspa::backRender(Player * player)
{

	_img->setScale(3);	
	if (_Opposition)
	{
		_img->render(CAMERA->getRelativeV2(_renderPos), true);
	}
	else
	{
		_img->render(CAMERA->getRelativeV2(_renderPos), false);
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

void Voluspa::equip(Player* player)
{
}
