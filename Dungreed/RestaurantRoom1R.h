#pragma once
#include "Stage.h"
class RestaurantRoom1R :
    public Stage
{
public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

