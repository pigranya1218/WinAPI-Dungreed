#include "bombPouch.h"
#include "NormalProjectile.h"

void bombPouch::init()
{
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::RARE;
	_iconImg = IMAGE_MANAGER->findImage("BombPouch");
	
	_addStat.defense = 2;	
	_price = 1200;	
	_isExplosion = false;
	
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
	_isExplosion = true;
	if (_isExplosion)
	{
		NormalProjectile* projectile = new NormalProjectile;		
		float _angleY = 0;
		_angleY  = -(PI / 2);		
		projectile->setPosition(_renderPos);
		projectile->setSize(Vector2(200, 200));
		projectile->setTeam(OBJECT_TEAM::PLAYER);
		projectile->init("BombPouch0", _angleY, 700, true, false, 20, false, "BabyBatBulletFx", Vector2(100, 100));
		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::PLAYER;
		player->attack(projectile, attackInfo);
	}
}

void bombPouch::equip(Player* player)
{

}
