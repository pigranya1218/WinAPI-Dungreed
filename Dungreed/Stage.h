#pragma once

#include "EnemyManager.h"
#include "ObjectManager.h"
#include "ProjectileManager.h"
#include "NpcManager.h"
#include "AllEnums.h"
#include "LinearFunc.h"
#include "Attackinfo.h"
#include "MapTool.h"


class StageManager;

class Stage
{
protected:
	StageManager* _stageManager;
	Stage* _connectedStage[static_cast<int>(DIRECTION::END)]; // ����� ��������(�� �� �� ��)
	
	tagTileMap _tile[2000];
	Image* _tileImage;

	EnemyManager* _enemyMgr;
	ObjectManager* _objectMgr;
	ProjectileManager* _projectileMgr;
	NpcManager* _npcMgr;
	
	vector<FloatRect> _collisionGroundRects; // �簢�� ��
	vector<LinearFunc> _collisionGroundLines; // �밢�� ��
	vector<LinearFunc> _collisionPlatforms; // �÷��� ��
	
	bool _isVisited; // �湮�� ���������ΰ�? (UI �������� �׸��� ����)

public:
	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }
	virtual void init();
	virtual void release();
	virtual void update(float const elaspedTime);
	virtual void render();

	void loadMap(string mapName);
	void makeMapToLine(int startX, int startY, int currX, int currY, vector<vector<bool>>& isVisited);
	void moveTo(GameObject* object, Vector2 const moveDir); // GameObject�� moveDir �������� �浹������ ����ؼ� �̵���Ű�� �Լ�
	
	void attack(Projectile* projectile, AttackInfo* info);

	// �ǰ� üũ�� ���� ȣ��
	bool isHitEnemy(FloatRect* rc, AttackInfo* info);
	bool isHitEnemy(FloatCircle* circle, AttackInfo* info);

	inline Stage* getConnectedStage( DIRECTION const direction ) const { return _connectedStage[static_cast<int> (direction)];}
	bool isVisited() const { return _isVisited; }
	Vector2 getPlayerPos();
};