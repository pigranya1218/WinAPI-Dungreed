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
	Stage* _connectedStage[static_cast<int>(DIRECTION::END)]; // 연결된 스테이지(좌 우 상 하)
	
	EnemyManager* _enemyMgr;
	ObjectManager* _objectMgr;
	ProjectileManager* _projectileMgr;
	NpcManager* _npcMgr;
	
	vector<tagCollision> _collisionGrounds; // 땅
	vector<tagCollision> _collisionPlatforms; // 발판
	bool _isVisited; // 방문한 스테이지인가? (UI에서 그리기 위함)

public:
	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }
	virtual void init();
	virtual void release();
	virtual void update(float const elaspedTime);
	virtual void render();

	void moveTo(GameObject* object, Vector2 const moveDir); // GameObject를 moveDir 방향으로 충돌판정을 계산해서 이동시키는 함수
	void attack(FloatRect* rect, AttackInfo* info);
	void attack(FloatCircle* circle, AttackInfo* info);
	void attack(Projectile* projectile, AttackInfo* info);

	inline Stage* getConnectedStage( DIRECTION const direction ) const { return _connectedStage[static_cast<int> (direction)];}
	bool isVisited() const { return _isVisited; }
	Vector2 getPlayerPos();
};