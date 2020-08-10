#pragma once
#include "Object.h"

class ObjectManager
{
private:
	vector<Object*> _objects;

public:
	void init();
	void release();
	void update(float const elapsedTime);
	void render();
};

