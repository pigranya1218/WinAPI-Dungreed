#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
private:	
	float _speed;	// 속도
	float _range;	// 사정거리


public:
	void init();
	void update();
	void render();



};

