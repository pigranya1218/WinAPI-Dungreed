#pragma once
#include "Stage.h"
class StartRoom2 :
	public Stage
{
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

