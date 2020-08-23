#pragma once
#include "Item.h"
class watCher : public Item
{
private:
	Image* _img;
	Animation* _ani;
	Vector2 _renderPos;
	Vector2 _anglePos;
	
	int _x, _y;
	int _radius;
	int _fspeed;	
	float _angle = PI / 5;	
	bool _setitem;
public:
	virtual void init();
	virtual void release();
	virtual void update(Player* player, float const elapsedTime);
	virtual void backRender(Player* player);

	virtual bool isHit(Projectile* projectile) ;
};

