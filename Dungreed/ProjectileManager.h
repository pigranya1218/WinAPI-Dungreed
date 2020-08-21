#pragma once
#include "Projectile.h"

class Stage;
class EnemyManager;
class ObjectManager;

class ProjectileManager
{
private:

protected:
	Stage* _stage;
	EnemyManager* _enemyManager;
	ObjectManager* _objectManager;

	vector<Projectile*> _projectiles;

public:
	void init();
	void release();
	void update(float const elapsedTime);
	void render();

	void setStage(Stage* stage) { _stage = stage; }
	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
	void setObjectManager(ObjectManager* objectManager) { _objectManager = objectManager; }
	void moveTo(GameObject* gameObject, Vector2 moveDir, bool checkCollisionGround = true, bool checkCollisionPlatform = true);
	void addProjectile(Projectile* projectile) { projectile->setProjectileManager(this); _projectiles.push_back(projectile); }

	bool checkObjectCollision(Projectile* projectile, bool isOnceCollision); // ������Ʈ���� �浹 ó��
	bool checkEnemyCollision(Projectile* projectile, bool isOnceCollision); // isOnceCollision : �� �༮�� �ε����� �����
	bool checkPlayerCollision(Projectile* projectile, bool isOnceCollision);

	Vector2 getEnemyPos(Vector2 pos);
};

