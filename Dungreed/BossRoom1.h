#pragma once
#include "Stage.h"



class BossRoom1 : public Stage
{
private:

public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

