#pragma once
#include "Npc.h"

class AbilityNpc : public Npc
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

	virtual void clickMenu(int menuIndex); // Dialogue â���� �޴��� Ŭ����
};
