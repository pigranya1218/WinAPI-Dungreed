#include "DemonBoots.h"
#include "HeartOfCosmosProjectile.h"

void DemonBoots::init()
{
	_itemCode = 0x03303;
	_iconImg = IMAGE_MANAGER->findImage("DemonBoots");
	
	_price = 4300;
	
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
	HeartOfCosmosProjectile* projectile = new HeartOfCosmosProjectile;
	float _angleY = 0;
	_angleY = (-PI2 / 4);
	projectile->setPosition(_renderPos);
	_renderPos.y = _renderPos.y;
	projectile->setSize(Vector2(50, 100));
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	_pos.y = _renderPos.y*_angleY;
	_pos.x = _renderPos.x;
	projectile->init("DemonBoots0", _pos.y, 0, true, false, 8, false, "DemonBoots0", Vector2(150, 150), false);
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
