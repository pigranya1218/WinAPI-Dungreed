#pragma once

#include "EnemyManager.h"
#include "ObjectManager.h"
#include "ProjectileManager.h"
#include "NpcManager.h"
#include "AllEnums.h"
#include "LinearFunc.h"
#include "Attackinfo.h"
#include "MapTool.h"

class Player;
class StageManager;

class Stage
{
protected:
	StageManager* _stageManager;
	UIManager* _uiManager;
	Player* _player;

	Stage* _connectedStage[static_cast<int>(DIRECTION::END)]; // 연결된 스테이지(좌 우 상 하)
	
	tagTileMap _tile[MAXTILEX*MAXTILEY];
	Image* _tileImage;

	EnemyManager* _enemyMgr;
	ObjectManager* _objectMgr;
	ProjectileManager* _projectileMgr;
	NpcManager* _npcMgr;
	
	vector<FloatRect> _collisionGroundRects; // 사각형 땅
	vector<LinearFunc> _collisionGroundLines; // 대각선 땅
	vector<LinearFunc> _collisionPlatforms; // 플랫폼 땅
	
	bool _isVisited; // 방문한 스테이지인가? (UI 지도에서 그리기 위함)


	vector<DIRECTION> _direction;
	vector<DIRECTION>::iterator _viDirection;

	bool _OpenDirection[4];
	
	bool _isMade;

public:
	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }
	void setUIManager(UIManager* uiManager) { _uiManager = uiManager; }
	void setPlayer(Player* player) { _player = player; }
	virtual void init();
	virtual void release();
	virtual void update(float const elaspedTime);
	virtual void render();

	void loadMap(string mapName);
	void makeMapToLine(int startX, int startY, int currX, int currY, vector<vector<bool>>& isVisited);
	void moveTo(GameObject* object, Vector2 const moveDir, bool checkCollisionGround = true, bool checkCollisionPlatform = true); // GameObject를 moveDir 방향으로 충돌판정을 계산해서 이동시키는 함수

	// 몬스터와 플레이어 공동 사용
	void attack(Projectile* projectile, AttackInfo* info);

	// 몬스터의 공격 체크를 위해 호출
	void attack(FloatRect* rc, AttackInfo* info);
	void attack(FloatCircle* circle, AttackInfo* info);

	// 피격 체크를 위해 호출
	bool isHitEnemy(FloatRect* rc, AttackInfo* info);
	bool isHitEnemy(FloatCircle* circle, AttackInfo* info);

	bool isHitPlayer(Projectile* projectile, bool isOnceCollision);

	inline Stage* getConnectedStage( DIRECTION const direction ) const { return _connectedStage[static_cast<int> (direction)];}
	bool isVisited() const { return _isVisited; }
	Vector2 getPlayerPos();
	Vector2 getEnemyPos(const Vector2& pos);

	void showDamage(DamageInfo info, Vector2 pos);
	void showEnemyHp(float maxHp, float curHp, Vector2 pos);
	
	vector<DIRECTION> getStageDirection() {return _direction ; }
	vector<DIRECTION>::iterator getVItageDirection() { return _viDirection; }

	bool getOpenDirection(int num) { return _OpenDirection[num]; }
	bool getIsMade() { return _isMade; }
	void setIsMade(bool ismade) { _isMade = ismade; }
};