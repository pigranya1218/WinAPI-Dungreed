#pragma once
#include "Stage.h"
class DownStair1L :
	public Stage
{
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};
