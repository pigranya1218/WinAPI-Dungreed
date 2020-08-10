#pragma once

#include "EnemyManager.h"
#include "ObjectManager.h"
#include "ProjectileManager.h"
#include "NpcManager.h"
#include "AllEnums.h"

class Stage
{
private:
	Stage* _connectedStage[static_cast<int>(DIRECTION::END)]; // 연결된 스테이지(좌 우 상 하)
	EnemyManager* _enemyMgr;
	 ObjectManager* _objectMgr;
	ProjectileManager* _projectileMgr;
	NpcManager* _npcMgr;
	
	bool _isVisited; // 방문한 스테이지인가? (UI에서 그리기 위함)

public:
	virtual void init();
	virtual void release();
	virtual void update(float const timeElapsed);
	virtual void render();

	virtual void moveTo(GameObject& object, Vector2 const moveDir) = 0; // GameObject를 moveDir 방향으로 충돌판정을 계산해서 이동시키는 함수
	
	inline Stage* getConnectedStage( DIRECTION const direction ) const { return _connectedStage[static_cast<int> (direction)];}
	bool isVisited() const { return _isVisited; }
};