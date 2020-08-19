#pragma once
#include "Item.h"
class SpikeBall : public Item
{
private:
	Image* _img;

	FloatRect _crash;
	int _x, _y;
	float _angle = PI / 2;

	string _attackCode;

public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);
};

