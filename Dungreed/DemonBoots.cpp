#include "DemonBoots.h"
#include "HeartOfCosmosProjectile.h"
#include "GameScene.h"


void DemonBoots::init()
{
	_itemCode = 0x03303;
	_iconImg = IMAGE_MANAGER->findImage("DemonBoots");
	_itemName = L"악마의 부츠";
	_displayInfos.push_back(L"\"밟은 곳에 불이 붙습니다\"");
	_displayText = L"\"신는 사람이 뒤에 열기를 쫒기게 되는 신발\"";
	_price = 4300;	
	_Delay = 1.0;
	_Delay1 = 1.5;
}

void DemonBoots::release()
{
}

void DemonBoots::update(Player * player, float const elapsedTime)
{
	_random = RANDOM->getFromIntTo(0, 65);
	_renderPos = player->getPosition();	
	_renderPos.y = _renderPos.y - 15;
	_renderPos.x = _renderPos.x - 30;
	if (player->getIsStand()) {
		if (_Delay > 0)
		{
			_Delay = max(0, _Delay - elapsedTime);
		}
		if (_Delay1 > 0)
		{
			_Delay1 = max(0, _Delay1 - elapsedTime);
		}
		if (_Delay == 0)
		{
			_Delay = 1.0;
			_renderPos.x = _renderPos.x + _random;
			EFFECT_MANAGER->play("DemonBootsF", _renderPos, Vector2(60, 120), 0, false);
		}
		if (_Delay1 == 0)
		{
			_Delay1 = 1.0;
			_renderPos.x = _renderPos.x + _random;
			EFFECT_MANAGER->play("DemonBootsF", _renderPos, Vector2(60, 120), 0, false);
		}
	}
}

void DemonBoots::backRender(Player * player)
{
	
	
}

void DemonBoots::frontRender(Player * player)
{
}

void DemonBoots::displayInfo()
{
}

void DemonBoots::attack(Player * player)
{
}

void DemonBoots::attack(FloatRect * rect, AttackInfo * info)
{
}

void DemonBoots::attack(FloatCircle * circle, AttackInfo * info)
{
}

void DemonBoots::attack(Projectile * projectile, AttackInfo * info)
{
}

void DemonBoots::getHit(Vector2 const position)
{
}

void DemonBoots::dash(Player * player)
{
	
}

void DemonBoots::equip(Player * player)
{
	
}
