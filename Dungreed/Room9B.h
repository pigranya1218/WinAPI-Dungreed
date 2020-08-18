#pragma once
#include "Stage.h"
class Room9B :
	public Stage
{
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

