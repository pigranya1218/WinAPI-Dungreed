#pragma once

#include "EnemyManager.h"
#include "ObjectManager.h"
#include "ProjectileManager.h"
#include "NpcManager.h"
#include "AllEnums.h"

class Stage
{
private:
	Stage* _connectedStage[static_cast<int>(DIRECTION::END)]; // ����� ��������(�� �� �� ��)
	EnemyManager* _enemyMgr;
	 ObjectManager* _objectMgr;
	ProjectileManager* _projectileMgr;
	NpcManager* _npcMgr;
	
	bool _isVisited; // �湮�� ���������ΰ�? (UI���� �׸��� ����)

public:
	virtual void init();
	virtual void release();
	virtual void update(float const timeElapsed);
	virtual void render();

	virtual void moveTo(GameObject& object, Vector2 const moveDir) = 0; // GameObject�� moveDir �������� �浹������ ����ؼ� �̵���Ű�� �Լ�
	
	inline Stage* getConnectedStage( DIRECTION const direction ) const { return _connectedStage[static_cast<int> (direction)];}
	bool isVisited() const { return _isVisited; }
};