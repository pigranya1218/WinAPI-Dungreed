#pragma once
#include "Item.h"
class SilverBullet :public Item
{
private:

public:
	virtual void init();

	virtual void attack(Player* player, Projectile* projectile, AttackInfo* info)override; // źȯ�� �����Ű�� �Լ�
};

