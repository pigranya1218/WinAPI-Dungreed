#pragma once
#include "Item.h"

class HeartOfCosmos : public Item
{
private:
	Image* _img;	
	Vector2 _renderPos;
	int _x, _y;
	AccProjectile* projectile;
		
	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime());

public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);	
	virtual void dash(Player* player)override; // 플레이어가 대쉬했을 때
	
};

