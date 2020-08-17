#include "DemonBoots.h"
#include "NormalProjectile.h"

void DemonBoots::init()
{
	_itemCode = 0x03303;
	_iconImg = IMAGE_MANAGER->findImage("DemonBoots");
	
	_price = 4300;
	_isExplosion = false;
}

void DemonBoots::release()
{
}

void DemonBoots::update(Player * player, float const elapsedTime)
{
	_renderPos = player->getPosition();
}

void DemonBoots::backRender(Player * player)
{
	NormalProjectile* projectile = new NormalProjectile;
	projectile->setPosition(_renderPos);
	projectile->setSize(Vector2(50, 50));
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("DemonBoots0", 0, 0, true, false, 15, false, "", Vector2(0, 0), true);
	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	player->attack(projectile, attackInfo);
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
