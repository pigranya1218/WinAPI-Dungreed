#pragma once
#include "Item.h"
class MultiBullet : public Item
{
private:

public:
	virtual void init();

	virtual void attack(Projectile* projectile, AttackInfo* info); // źȯ�� �����Ű�� �Լ�
};

