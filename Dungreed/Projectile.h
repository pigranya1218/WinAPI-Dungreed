#pragma once
#include "GameObject.h"

class ProjectileManager;

class Projectile : public GameObject
{
protected:
	ProjectileManager* _projectileMgr;

public:
	virtual void release() = 0;
	virtual void update(float elapsedTime) = 0;
	virtual void render() = 0;

	void setProjectileManager(ProjectileManager* projectileMgr) { _projectileMgr = projectileMgr; }
};