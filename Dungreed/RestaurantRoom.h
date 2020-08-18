#pragma once
#include "Stage.h"
#include "MapTool.h"

class RestaurantRoom : public Stage
{
private:
	
	
	int _currentIndex;

public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

