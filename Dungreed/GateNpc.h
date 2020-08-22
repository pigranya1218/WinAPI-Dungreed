#pragma once
#include "Npc.h"

class StageManager;

class GateNpc : public Npc
{
private:
	Image* _img;
	Animation* _ani;

	bool _move;
	Vector2 _roomIndex;

	StageManager* _stageManager;

	

public:
	virtual void init(Vector2 pos, DIRECTION direction);
	virtual void release();
	virtual void update(float timeElapsed);
	virtual void interaction();
	virtual void render();

	void move(Vector2 roomIndex);
};

