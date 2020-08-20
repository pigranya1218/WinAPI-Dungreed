#pragma once
#include "Stage.h"
class RestaurantRoom2LR :
	public Stage
{
public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

