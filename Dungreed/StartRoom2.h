#pragma once
#include "Stage.h"
class StartRoom2 :
	public Stage
{
private:
	Image* _img;
	Animation* _ani;

public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

