#pragma once
#include "Stage.h"

class TestStage : public Stage
{
private:

public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};

