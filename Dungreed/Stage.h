#pragma once

#include "EnemyManager.h"
#include "ObjectManager.h"
#include "ProjectileManager.h"
#include "NpcManager.h"
#include "AllEnums.h"
#include "LinearFunc.h"
#include "Attackinfo.h"

class StageManager;

class Stage
{
protected:
	struct tagCollision
	{
		LinearFunc func;
		LINEAR_VALUE_TYPE collision;
	};

protected:
	StageManager* _stageManager;
	Stage* _connectedStage[static_cast<int>(DIRECTION::END)]; // ����� ��������(�� �� �� ��)
	
	EnemyManager* _enemyMgr;
	ObjectManager* _objectMgr;
	ProjectileManager* _projectileMgr;
	NpcManager* _npcMgr;
	
	vector<tagCollision> _collisionGrounds; // ��
	vector<tagCollision> _collisionPlatforms; // ����
	bool _isVisited; // �湮�� ���������ΰ�? (UI���� �׸��� ����)

public:
	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }
	virtual void init();
	virtual void release();
	virtual void update(float const elaspedTime);
	virtual void render();

	void moveTo(GameObject* object, Vector2 const moveDir); // GameObject�� moveDir �������� �浹������ ����ؼ� �̵���Ű�� �Լ�
	void attack(FloatRect* rect, AttackInfo* info);
	void attack(FloatCircle* circle, AttackInfo* info);
	void attack(Projectile* projectile, AttackInfo* info);

	inline Stage* getConnectedStage( DIRECTION const direction ) const { return _connectedStage[static_cast<int> (direction)];}
	bool isVisited() const { return _isVisited; }
	Vector2 getPlayerPos();
};