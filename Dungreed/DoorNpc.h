#pragma once
#include "Npc.h"

class StageManager;

class DoorNpc : public Npc
{
private:
	Image* _img;
	Animation* _ani;
private:
	void setInfo(); // Ÿ�Կ� ���� ����
	StageManager* _stageManager;

public:
	void setType(NPC_TYPE type) { _type = type; }
	virtual void init(Vector2 pos, DIRECTION direction);
	virtual void release();
	virtual void update(float elapsedTime);
	virtual void interaction();
	virtual void render();
};

