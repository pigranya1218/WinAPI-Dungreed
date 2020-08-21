#pragma once
#include "GameObject.h"
#include "AttackInfo.h"
#include "Projectile.h"

class ObjectManager;

class Object : public GameObject
{
protected:
	ObjectManager* _objectMgr;
	vector<size_t> _attackedId;
	int _objectCode;

public:
	void setObjectManager(ObjectManager* objectMgr) { _objectMgr = objectMgr; }

	virtual void release() {}
	virtual void update(float elapsedTime) {}
	virtual void render() {}

	bool isHit(FloatRect* rect, AttackInfo* info);
	bool isHit(FloatCircle* circle, AttackInfo* info);
	bool isHit(Projectile* projectile);

	virtual bool hitEffect(FloatRect* rect, AttackInfo* info) { return false; }
	virtual bool hitEffect(FloatCircle* circle, AttackInfo* info) { return false; }
	virtual bool hitEffect(Projectile* projectile) { return false; }
};