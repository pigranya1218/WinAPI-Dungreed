#pragma once
#include "Item.h"
class Seeri : public Item
{
private:
	Image* _img;
	Animation* _ani;

	Vector2 _renderPos;
	DIRECTION _direction;

public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);
	virtual void attack(Player* player);
};

