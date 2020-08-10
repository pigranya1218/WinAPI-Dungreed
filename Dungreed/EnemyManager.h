#pragma once
#include "Enemy.h"

class EnemyManager
{
private:
	vector<Enemy*> _enemies;

public:
	void init();
	void release();
	void update(float const timeElapsed);
	void render();
};

