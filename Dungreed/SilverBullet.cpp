#include "SilverBullet.h"

void SilverBullet::init()
{
	//악세서리 타입
	_itemCode = 0x03312;
	_iconImg = IMAGE_MANAGER->findImage("SilverBullet");

	//악세서리 옵션
	
	_itemName = L"은 탄환";
	_displayInfos.push_back(L"총알이 적을 관통");
	_displayText = L"\"이 세상에 명쾌한 해결책 따위는 없어.\"";
	
	//악세서리 가격
	_price = 3200;
}

void SilverBullet::attack(Player * player, Projectile * projectile, AttackInfo * info)
{
	projectile->setUseEnemyCollision(false);
}
