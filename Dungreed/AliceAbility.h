#pragma once
#include "Item.h"

class AliceAbility : public Item
{
private:
	Image* _img;
	Animation* _ani;
	bool _isEnemyIn; // 적이 반경 안에 존재하는지

public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
};

