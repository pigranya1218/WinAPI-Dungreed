#pragma once
#include "Item.h"
class miniEarth : public Item
{
private:
	Image* _img;
	Animation* _ani;
	Vector2 _renderPos;	
	int _x, _y;
	float _angle;
public:

	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);
	
};

