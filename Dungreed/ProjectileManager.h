#pragma once
#include "Projectile.h"

class Stage;
class EnemyManager;

class ProjectileManager
{
private:

protected:
	Stage* _stage;
	EnemyManager* _enemyManager;

	vector<Projectile*> _projectiles;

public:
	void init();
	void release();
	void update(float const elapsedTime);
	void render();

	void setStage(Stage* stage) { _stage = stage; }
	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
	void moveTo(GameObject* gameObject, Vector2 moveDir, bool checkCollisionGround = true, bool checkCollisionPlatform = true);
	void addProjectile(Projectile* projectile) { projectile->setProjectileManager(this); _projectiles.push_back(projectile); }

	bool checkEnemyCollision(Projectile* projectile, bool isOnceCollision); // isOnceCollision : ÇÑ ³à¼®ÀÌ ºÎµúÈ÷¸é »ç¶óÁü
	bool checkPlayerCollision(Projectile* projectile, bool isOnceCollision);

	Vector2 getEnemyPos(Vector2 pos);
};

