#pragma once
#include "Stage.h"
class BossRoomBef1R :
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

