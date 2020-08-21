#pragma once
#include "Stage.h"
class Room7RT : public Stage
{
public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

