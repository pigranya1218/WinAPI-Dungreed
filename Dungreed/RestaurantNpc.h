#pragma once
#include "Npc.h"

// 식당 NPC
class RestaurantNpc : public Npc
{
private:
	Image* _img;
	Animation* _ani;

public:
	virtual void init(Vector2 pos, DIRECTION direction);
	virtual void release();
	virtual void update(float timeElapsed);
	virtual void interaction();
	virtual void render();

	virtual void clickMenu(int menuIndex); // Dialogue 창에서 메뉴를 클릭함

};

