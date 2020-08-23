#pragma once
#include "Item.h"
class IceBall : public Item
{
private:
	Image* _img;
	Animation* _ani;

	FloatRect _crash;
	int _x, _y;
	float _angle;
	bool _setitem;
	int _radius;
	int _fspeed;

	string _attackCode;
	float _elapsedTime;


public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);
	
};

