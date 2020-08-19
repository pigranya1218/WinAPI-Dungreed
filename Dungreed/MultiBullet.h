#pragma once
#include "Item.h"
class MultiBullet : public Item
{
private:

public:
	virtual void init();

	virtual void attack(Projectile* projectile, AttackInfo* info); // 탄환을 변경시키는 함수
};

