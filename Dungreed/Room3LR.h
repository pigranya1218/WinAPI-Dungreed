#pragma once
#include "Stage.h"
class Room3LR :
	public Stage
{
private:
	Image* _torchImg;
	Animation* _torchAni;

public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

