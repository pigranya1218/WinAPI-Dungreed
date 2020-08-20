#pragma once
#include "Item.h"
class MagnifyingGlass : public Item
{
private:
	ITEM_TYPE ITEM_TYPE;
public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);	
	virtual void attack(Player* player, Projectile* projectile, AttackInfo* info)override; // 탄환을 변경시키는 함수

};

