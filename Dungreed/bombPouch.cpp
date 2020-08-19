#include "bombPouch.h"
#include "NormalProjectile.h"

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
	NormalProjectile* projectile = new NormalProjectile;
		float _angleY = 0;
		_angleY  = -PI2/4;
		_renderPos.x = _renderPos.x + 100;		
		projectile->setPosition(_renderPos);
		projectile->setSize(Vector2(200, 200));
		projectile->setTeam(OBJECT_TEAM::PLAYER);

		//projectile->init("BombPouch0", _angleY, 750, true, true, 20, false, "BombPouch2", Vector2(250, 250), 0.4, true);
		projectile->init("BombPouch0", "BombPouch2", Vector2(250, 250), Vector2(750, 750), 0.4, _angleY, true, true, 20, false, false, true, false);

		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::PLAYER;
		player->attack(projectile, attackInfo);
	
}

void bombPouch::equip(Player* player)
{

}

