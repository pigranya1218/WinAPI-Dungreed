#include "DemonBoots.h"
#include "AccProjectile.h"
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
	_renderPos.y = _renderPos.y - 20;
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
			
			AccProjectile* projectile = new AccProjectile;
			projectile->setPosition(_renderPos);
			projectile->setSize(Vector2(50, 130));
			projectile->setTeam(OBJECT_TEAM::PLAYER);
			projectile->init("DemonBoots0", _renderPos, 0, true, false, 13, false, "DemonBoots0", Vector2(0, 0), 10, false, false, false, false);
			string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime());
			AttackInfo* attackInfo = new AttackInfo;
			attackInfo->team = OBJECT_TEAM::PLAYER;
			attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
			attackInfo->maxDamage = 5;
			attackInfo->minDamage = 3;
			player->attack(projectile, attackInfo);
		}
		if (_Delay1 == 0)
		{
			_Delay1 = 1.0;
			_renderPos.x = _renderPos.x + _random;
			
			AccProjectile* projectile = new AccProjectile;
			projectile->setPosition(_renderPos);
			projectile->setSize(Vector2(50, 130));
			projectile->setTeam(OBJECT_TEAM::PLAYER);
			projectile->init("DemonBoots0", _renderPos, 0, true, false, 13, false, "DemonBoots0", Vector2(0, 0), 10, false, false, false, false);
			string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime());
			AttackInfo* attackInfo = new AttackInfo;
			attackInfo->team = OBJECT_TEAM::PLAYER;
			attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
			attackInfo->maxDamage = 5;
			attackInfo->minDamage = 3;
			player->attack(projectile, attackInfo);
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
