#pragma once
#include "Projectile.h"

class ProjectileManager
{
private:
protected:
	vector<Projectile*> _projectiles;

public:
	void init();
	void release();
	void update(float const elapsedTime);
	void render();
};

