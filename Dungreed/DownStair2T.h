#pragma once
#include "Stage.h"
class DownStair2T :
    public Stage
{
private:
	Image* _gateImg;

public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

