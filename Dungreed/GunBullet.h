#pragma once
#include "Projectile.h"
#include "ProjectileManager.h"

//class ProjectileManager;

class GunBullet : public Projectile
{
private:
	ProjectileManager* _projectileMng;
public:
	virtual void init(Vector2 pos);
	virtual void release();
	virtual void update(float timeElapsed);
	virtual void render();
	void fire(Vector2 const pos, float const angle, int itemType);
	void move();
};

