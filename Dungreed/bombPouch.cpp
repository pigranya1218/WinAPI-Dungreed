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

void bombPouch::displayInfo()
{
}

void bombPouch::attack(Player* player)
{
}

void bombPouch::attack(FloatRect * rect, AttackInfo * info)
{
}

void bombPouch::attack(FloatCircle * circle, AttackInfo * info)
{
}

void bombPouch::attack(Projectile * projectile, AttackInfo * info)
{
}

void bombPouch::getHit(Vector2 const position)
{
}

void bombPouch::dash(Player * player)
{
	AccProjectile* projectile = new AccProjectile;
		
		_renderPos.x = _renderPos.x + 100;		
		projectile->setPosition(_renderPos);
		projectile->setSize(Vector2(200, 200));
		projectile->setTeam(OBJECT_TEAM::PLAYER);

		// projectile->init("BombPouch0", _angleY, 750, true, true, 20, false, "BombPouch2", Vector2(250, 250), 0.4, true);
		// projectile->init("BombPouch0", , Vector2(250, 250), Vector2(250, 250), Vector2(750, 750), 0.4, _angleY, true, true, 20, false, false, true, false);

		string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime());
		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::PLAYER;
		attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
		attackInfo->maxDamage = 5;
		attackInfo->minDamage = 3;
		player->attack(projectile, attackInfo);
	
}

void bombPouch::equip(Player* player)
{

}

