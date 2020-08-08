#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
private:	
	Image* _img;

	float _speed;	// �ӵ�
	float _range;	// �����Ÿ�
	

public:
	void init(string imageName);
	void release();
	void update();
	void render();



};

