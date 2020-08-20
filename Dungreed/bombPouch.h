#pragma once
#include "Item.h"
class bombPouch : public Item
{
private:

	
	Image* _img;	
	Vector2 _renderPos;
	int _x, _y;	
	

public:

	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);	
	virtual void dash(Player* player)override; // �÷��̾ �뽬���� ��
	
};

