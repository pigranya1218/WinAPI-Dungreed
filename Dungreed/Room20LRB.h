#pragma once
#include "Stage.h"
class Room20LRB :
    public Stage
{
public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

