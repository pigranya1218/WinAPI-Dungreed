#pragma once
#include "GameObject.h"
#include "AttackInfo.h"

class ProjectileManager;

class Projectile : public GameObject
{
protected:
	ProjectileManager* _projectileMgr;
	AttackInfo* _info;

	Vector2 _renderSize;
	Vector2 _effectSize;
	Vector2		_force;				// 투사체 날아가는 힘
	float		_angleRadian;		// 투사체 날아가는 각도
	bool		_useCollsionEnemy;	// 투사체를 에너미와 충돌시킬 것인가


public:
	virtual void release() { delete _info; };
	virtual void update(float elapsedTime) {};
	virtual void render() {};

	void setProjectileManager(ProjectileManager* projectileMgr) { _projectileMgr = projectileMgr; }
	void setAttackInfo(AttackInfo* info) { _info = info; }
	AttackInfo* getAttackInfo() { return _info; }

	Vector2 getRenderSize() { return _renderSize; }
	void setRenderSize(Vector2 renderSize) { _renderSize = renderSize; }
	Vector2 getEffectSize() { return _effectSize; }
	void setEffectSize(Vector2 effectSize) { _effectSize = effectSize; }

	Vector2 getForce() { return _force; }
	void setForce(Vector2 force) { _force = force; }

	float getAngleRadian() { return _angleRadian; }
	void setAngleRadian(float angleRadian) { _angleRadian = angleRadian; }

	bool getUseEnemyCollision() { return _useCollsionEnemy; }
	void setUseEnemyCollision(bool useCollision) { _useCollsionEnemy = useCollision; };
};