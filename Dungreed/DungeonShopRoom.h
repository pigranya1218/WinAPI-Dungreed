#pragma once
#include "Stage.h"

class DungeonShopRoom :public Stage
{
public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();
};
