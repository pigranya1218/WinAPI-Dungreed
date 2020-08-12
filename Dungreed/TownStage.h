#pragma once
#include "GameNode.h"


class TownStage : public GameNode
{
private:


public:
	HRESULT init();
	void release();
	void update();
	void render();
	
};

