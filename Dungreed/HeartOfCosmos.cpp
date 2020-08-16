#include "HeartOfCosmos.h"
#include "NormalProjectile.h"
void HeartOfCosmos::init()
{
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::HIGH;
	_iconImg = IMAGE_MANAGER->findImage("HeartOfCosmos");

	_addStat.defense = 2;
	_price = 4300;
	_isExplosion = false;
}

void HeartOfCosmos::release()
{
}

void HeartOfCosmos::update(Player * player, float const elapsedTime)
{
	_renderPos = player->getPosition();
}

void HeartOfCosmos::backRender(Player * player)
{
}

void HeartOfCosmos::frontRender(Player * player)
{
}

void HeartOfCosmos::displayInfo()
{
}

void HeartOfCosmos::attack(Player * player)
{
}

void HeartOfCosmos::attack(FloatRect * rect, AttackInfo * info)
{
}

void HeartOfCosmos::attack(FloatCircle * circle, AttackInfo * info)
{
}

void HeartOfCosmos::attack(Projectile * projectile, AttackInfo * info)
{
}

void HeartOfCosmos::getHit(Vector2 const position)
{
}

void HeartOfCosmos::dash(Player * player)
{
	_isExplosion = true;
	if (_isExplosion)
	{
		NormalProjectile* projectile = new NormalProjectile;		
		projectile->setPosition(_renderPos);
		projectile->setSize(Vector2(200, 200));
		projectile->setTeam(OBJECT_TEAM::PLAYER);
		projectile->init("HeartOfCosmos0", 0, 0, true, false, 15, false, "", Vector2(0, 0),false);
		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::PLAYER;
		player->attack(projectile, attackInfo);
	}
}

void HeartOfCosmos::equip(Player * player)
{
}
