#include "bombPouch.h"
#include "NormalProjectile.h"

void bombPouch::init()
{
	_itemCode = 0x03201;
	_iconImg = IMAGE_MANAGER->findImage("BombPouch");
	
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
		_renderPos.y = _renderPos.y ;
		projectile->setPosition(_renderPos);
		projectile->setSize(Vector2(200, 200));
		projectile->setTeam(OBJECT_TEAM::PLAYER);
		projectile->init("BombPouch0", _angleY, 10, true, true, 20, true, "BombPouch2", Vector2(250, 250), 1000, true);
		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::PLAYER;
		player->attack(projectile, attackInfo);
	
}

void bombPouch::equip(Player* player)
{

}

