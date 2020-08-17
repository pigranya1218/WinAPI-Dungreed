#pragma once
#include "Npc.h"

// ½Ä´ç NPC
class RestaurantNpc : public Npc
{
private:
	Image* _img;
	Animation* _ani;

public:
	virtual void init(Vector2 pos, DIRECTION direction);
	virtual void release();
	virtual void update(float timeElapsed);
	virtual void render();
};

