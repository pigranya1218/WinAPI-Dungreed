#include "HeartOfCosmos.h"
#include "AccProjectile.h"
void HeartOfCosmos::init()
{
	_itemCode = 0x03307;
	_iconImg = IMAGE_MANAGER->findImage("HeartOfCosmos");
	_itemName = L"우주의 심장";
	_displayInfos.push_back(L"대쉬한 자리에 에너지체를 남김");
	_displayText = L"\"우주를 정복할 수 있는 힘을 가질 수 있을까?' 라는 물음에서 시작된 결정체""\"";	
	
	_price = 4300;
	
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


void HeartOfCosmos::dash(Player * player)
{

	AccProjectile* projectile = new AccProjectile;
	projectile->setPosition(_renderPos);
	projectile->setSize(Vector2(330, 300));
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("HeartOfCosmos0", _renderPos, 0, true, false, 13, false, "HeartOfCosmosF", Vector2(0, 0),10,false,false,false,false);
	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime());	
	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	attackInfo->madeByWeapon = false;
	attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	attackInfo->maxDamage = 5;
	attackInfo->minDamage = 3;
	player->attack(projectile, attackInfo);	
	

}


