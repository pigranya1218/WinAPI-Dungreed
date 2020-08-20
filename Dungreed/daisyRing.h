#pragma once
#include "Item.h"
#define OPTIONMAX 13



class DaisyRing : public Item
{
private:
	

	int _DaisyRingStat[11];
	int _count;
	
	

public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);	
	


};

