#pragma once

#include "EnemyManager.h"
#include "ObjectManager.h"
#include "ProjectileManager.h"
#include "AllEnums.h"

class Stage
{
private:
	Stage* _connectedStage[static_cast<int>(DIRECTION::END)]; // 연결된 스테이지(좌 우 상 하)
	EnemyManager _enemyManager;
	ObjectManager _objectManager;
	ProjectileManager _projectileManager;
	
	bool _isVisited; // 방문한 스테이지인가? (UI에서 그리기 위함)

public:
	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update(float const timeElapsed) = 0;
	virtual void render() = 0;

	virtual void moveTo(GameObject& object, Vector2 const moveDir) = 0; // GameObject를 moveDir 방향으로 충돌판정을 계산해서 이동시키는 함수
	
	inline Stage* getConnectedStage( DIRECTION const direction ) const { return _connectedStage[static_cast<int> (direction)];}
	bool isVisited() const { return _isVisited; }
};