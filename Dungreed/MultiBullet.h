#pragma once
#include "Item.h"
class MultiBullet : public Item
{
private:

public:
	virtual void init();

	virtual void attack(Player* player, Projectile* projectile, AttackInfo* info)override; // 탄환을 변경시키는 함수
};

