#pragma once
#include "Item.h"
class Wingboots : public Item
{
private:

public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);
	
};

