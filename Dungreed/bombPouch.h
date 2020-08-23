#pragma once
#include "Item.h"
class bombPouch : public Item
{
private:

		
	Vector2 _renderPos;
	
	

public:

	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);	
	virtual void dash(Player* player)override; // 플레이어가 대쉬했을 때
	
};

