#pragma once
#include "Stage.h"
class StartRoom2 :
	public Stage
{
private:
	Image* _img;
	Animation* _ani;

	Image* _torchImg;
	Animation* _torchAni;
public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();

};

