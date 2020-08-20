#pragma once
#include "Item.h"
class DemonBoots : public Item
{
private:
	Image* _img;	
	Vector2 _renderPos;
	float _Delay;   // �� ��Ÿ��
	float _Delay1;   // �� ��Ÿ��
	int _random;

public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);
	virtual void frontRender(Player* player);

};

