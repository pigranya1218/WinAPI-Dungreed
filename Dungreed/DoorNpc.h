#pragma once
#include "Npc.h"

class DoorNpc : public Npc
{
private:
	Image* _img;
	Animation* _ani;

private:
	void setInfo(); // 타입에 따른 관리

public:
	void setType(NPC_TYPE type) { _type = type; }
	virtual void init(Vector2 pos, DIRECTION direction);
	virtual void release();
	virtual void update(float elapsedTime);
	virtual void interaction();
	virtual void render();
};

