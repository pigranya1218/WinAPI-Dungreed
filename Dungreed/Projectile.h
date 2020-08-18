#pragma once
#include "GameObject.h"
#include "AttackInfo.h"

class ProjectileManager;

class Projectile : public GameObject
{
protected:
	ProjectileManager* _projectileMgr;
	AttackInfo* _info;

public:
	virtual void release() { delete _info; };
	virtual void update(float elapsedTime) = 0;
	virtual void render() = 0;

	void setProjectileManager(ProjectileManager* projectileMgr) { _projectileMgr = projectileMgr; }
	void setAttackInfo(AttackInfo* info) { _info = info; }
	AttackInfo* getAttackInfo() { return _info; }
};