#pragma once
#include "Stage.h"


class Room1 : public Stage
	
{
public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};
