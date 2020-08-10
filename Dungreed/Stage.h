#pragma once

#include "EnemyManager.h"
#include "ObjectManager.h"
#include "ProjectileManager.h"
#include "AllEnums.h"

class Stage
{
private:
	Stage* _connectedStage[static_cast<int>(DIRECTION::END)]; // ����� ��������(�� �� �� ��)
	EnemyManager _enemyManager;
	ObjectManager _objectManager;
	ProjectileManager _projectileManager;
	
	bool _isVisited; // �湮�� ���������ΰ�? (UI���� �׸��� ����)

public:
	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update(float const timeElapsed) = 0;
	virtual void render() = 0;

	virtual void moveTo(GameObject& object, Vector2 const moveDir) = 0; // GameObject�� moveDir �������� �浹������ ����ؼ� �̵���Ű�� �Լ�
	
	inline Stage* getConnectedStage( DIRECTION const direction ) const { return _connectedStage[static_cast<int> (direction)];}
	bool isVisited() const { return _isVisited; }
};