#pragma once
#include "Stage.h"
class BossRoom1 :
	public Stage
{

private:
	bool _isEventScene;
	float _timeCount;

	Image* _torchImg;
	Animation* _torchAni;

private:
	void startEventScene();

public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();


};

