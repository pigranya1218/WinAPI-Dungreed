#pragma once
#include "Stage.h"
class Room2LTR :
	public Stage
{
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

