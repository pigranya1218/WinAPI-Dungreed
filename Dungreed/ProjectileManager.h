#pragma once
#include "Projectile.h"

class Stage;

class ProjectileManager
{
private:

protected:
	Stage* _stage;

	vector<Projectile*> _projectiles;

public:
	void init();
	void release();
	void update(float const elapsedTime);
	void render();

	void setStage(Stage* stage) { _stage = stage; }
	void moveTo(GameObject* gameObject, Vector2 moveDir);
	void addProjectile(Projectile* projectile) { _projectiles.push_back(projectile); }
};

