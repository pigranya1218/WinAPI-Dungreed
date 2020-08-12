#pragma once
#include "GameNode.h"
//#include "Player.h"

class playGround : public GameNode
{	

private:
	//Player* _player;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

