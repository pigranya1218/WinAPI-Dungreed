#pragma once
#include "Item.h"
class Voluspa : public Item
{
private:
	Image* _img;
	Vector2 _renderPos;
	Vector2 _location;
	bool _Opposition;
	float _currAttackDelay;
public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);
	
};

