#pragma once
#include "Projectile.h"

class ProjectileManager
{
private:

protected:
	vector<Projectile*> _projectiles;
	vector<Projectile*> _vBullet;

public:
	void init();
	void release();
	void update(float const elapsedTime);
	void render();
	vector<Projectile*> getProjectile() { return _projectiles; }
	void fire();
};

