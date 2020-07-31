#pragma once
#include "GameNode.h"

class playGround : public GameNode
{	

private:

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

