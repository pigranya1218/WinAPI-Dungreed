#include "bombPouch.h"
#include "AccProjectile.h"

void bombPouch::init()
{
	_itemCode = 0x03201;
	_iconImg = IMAGE_MANAGER->findImage("BombPouch");
	_itemName = L"ÆøÅº ÁÖ¸Ó´Ï";
	_displayInfos.push_back(L"\"´ë½¬ÇÑ ÀÚ¸®¿¡ ÆøÅºÀ» ³²±è\"");
	_displayText = L"\"ÆøÅºÀÌ °¡µæ ´ã±ä ÁÖ¸Ó´Ï\"";
	_addStat.defense = 2;		
	_price = 1200;	
	
	
}

void bombPouch::release()
{
}

void bombPouch::update(Player* player, float const elapsedTime)
{
	_renderPos = player->getPosition();	

	
}

void bombPouch::frontRender(Player* player)
{
	

	

}

void bombPouch::backRender(Player* player)
{
	

}


void bombPouch::dash(Player * player)
{
	AccProjectile* projectile = new AccProjectile;
		
		_renderPos.x = _renderPos.x ;		
		projectile->setPosition(_renderPos);
		
		projectile->setTeam(OBJECT_TEAM::PLAYER);		 		
		projectile->init("BombPouch0", "BombPouch2", 1.3f, Vector2(150, 150), Vector2(230, 230), Vector2(500, 500), 500, PI/2, true, true, 15, false, true, true, false);
		
		string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime());
		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::PLAYER;
		attackInfo->madeByWeapon = false; 
		attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
		attackInfo->maxDamage = 5;
		attackInfo->minDamage = 3;
		player->attack(projectile, attackInfo);
	
}



