#pragma once
#include "Stage.h"
class Room5LR :
	public Stage
{
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

