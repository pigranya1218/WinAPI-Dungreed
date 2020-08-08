#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
private:	
	Image* _img;

	float _speed;	// 속도
	float _range;	// 사정거리
	

public:
	void init(string imageName);
	void release();
	void update();
	void render();



};

