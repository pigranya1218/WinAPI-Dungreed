#pragma once
#include "GameNode.h"


class TownStage : public GameNode
{
private:
	Camera _camera;


public:
	HRESULT init();
	void release();
	void update();
	void render();
	
};

