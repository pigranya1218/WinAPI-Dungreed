#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
private:	
	float _speed;	// �ӵ�
	float _range;	// �����Ÿ�


public:
	void init();
	void update();
	void render();



};

