#pragma once
#include "Stage.h"
class Room4LRB :
    public Stage
{
public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

