#include "bombPouch.h"
#include "NormalProjectile.h"

void bombPouch::init()
{
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::RARE;
	_iconImg = IMAGE_MANAGER->findImage("BombPouch");
	
	_addStat.defense = 2;
	
	_price = 1200;

	
	_isBoom = false;

}

void bombPouch::release()
{
}

void bombPouch::update(Player* player, float const elapsedTime)
{
	_maxDash = player->getMaxDash();
	_currDash = player->getCurrDash();
	int _Difference = _maxDash - _currDash ;	
	_renderPos = player->getPosition();
	


	if (_maxDash - _Difference == _currDash && _maxDash != _currDash )
	{
		
			_isBoom = true;
				
	}
	else
	{
		_isBoom = false;
	}
	
	
	if (_isBoom)
	{

		NormalProjectile* projectile = new NormalProjectile;
		Vector2 shootPos = _renderPos;
		float length = 60 * 0.3f; // 길이만큼
		int y = 0;

		shootPos.y += -sinf(PI / 2) * length;
		projectile->setPosition(shootPos);
		projectile->setSize(Vector2(100, 100));
		projectile->setTeam(OBJECT_TEAM::PLAYER);
		projectile->init("BombPouch0", y, 10, true, false, 20, false, "BabyBatBulletFx", Vector2(100, 100));
		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::PLAYER;
		player->attack(projectile, attackInfo);

	}
	
}

void bombPouch::frontRender(Player* player)
{

}

void bombPouch::backRender(Player* player)
{
	
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_RC));
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

void bombPouch::equip(Player* player)
{
	
	

}
