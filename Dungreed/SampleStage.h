#pragma once
#include "GameNode.h"

class SampleStage : public GameNode
{

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

