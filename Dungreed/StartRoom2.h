#pragma once
#include "Stage.h"
class StartRoom2 :
	public Stage
{
public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

