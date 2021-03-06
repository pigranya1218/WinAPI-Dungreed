#pragma once

#include "EnemyManager.h"
#include "ObjectManager.h"
#include "DoorObject.h"
#include "ProjectileManager.h"
#include "NpcManager.h"
#include "AllEnums.h"
#include "LinearFunc.h"
#include "Attackinfo.h"
#include "MapTool.h"

class Player;
class StageManager;

struct tagShowNpc
{
	Image* icon;
	NPC_TYPE type;
};

enum class STAGE_STATE : int
{
	IDLE = 0, // 대기 상태
	START, // 몬스터 소환하기
	FINISH, // 끝난 상태
	END
};

struct tagEnemySpawn // 적의 소환 위치
{
	ENEMY_TYPE type;
	Vector2 pos;
	int phase = 1;
};

struct tagChest // 보물상자 소환
{
	bool spawn = false; // 보물상자 소환 여부
	NPC_TYPE type;
	Vector2 pos;
};

class Stage
{
protected:
	StageManager* _stageManager;
	UIManager* _uiManager;
	Player* _player;

	STAGE_STATE _state;
	vector<tagEnemySpawn> _spawnEnemies;
	tagChest _spawnChest;
	float _spawnDelay;
	int _spawnIndex;
	int _spawnPhase;

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
	bool _isGoNextStage; // 다음 스테이지로 넘어갈텐가

	vector<bool> _isWall;
	vector<Vector2> _respawnPosition; // 플레이어가 리스폰될 위치
	vector<DoorObject*> _doors;



	Synthesize(ROOMTYPE, _roomType, RoomType)



public:
	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }
	void setUIManager(UIManager* uiManager) { _uiManager = uiManager; }
	void setPlayer(Player* player) { _player = player; }

	virtual void init();
	virtual void enter(int enterType); // enterType 0 ~ 3 : L T R B, 4 : DOOR
	virtual void release();
	virtual void update(float const elaspedTime);
	virtual void render();

	void loadMap(string mapName);
	void makeMapToLine(int startX, int startY, int currX, int currY, vector<vector<bool>>& isVisited);
	void moveTo(GameObject* object, Vector2 const moveDir, bool checkCollisionGround = true, bool checkCollisionPlatform = true); // GameObject를 moveDir 방향으로 충돌판정을 계산해서 이동시키는 함수

	// 적과 플레이어 공동 사용
	void attack(Projectile* projectile, AttackInfo* info);

	// 적의 공격 체크를 위해 호출
	void attack(FloatRect* rc, AttackInfo* info);
	void attack(FloatCircle* circle, AttackInfo* info);

	// 적의 피격 체크를 위해 호출
	bool isHitEnemy(FloatRect* rc, AttackInfo* info);
	bool isHitEnemy(FloatCircle* circle, AttackInfo* info);

	// 플레이어의 피격 체크를 위해 호출
	bool isHitPlayer(Projectile* projectile, bool isOnceCollision);

	inline Stage* getConnectedStage( DIRECTION const direction ) const { return _connectedStage[static_cast<int> (direction)];}
	bool isVisited() const { return _isVisited; }
	
	Vector2 getPlayerPos();
	Vector2 getEnemyPos(const Vector2& pos);
	vector<FloatRect> getEnemyRects();

	void showDamage(DamageInfo info, Vector2 pos);
	void showEnemyHp(float maxHp, float curHp, Vector2 pos);
	
	void setWall(vector<bool> isWall) { _isWall = isWall; }
	vector<bool> getWall() {return _isWall;}

	void makeDoor(Vector2 pos, DIRECTION direction);
	void makeDoorAuto();

	bool isPlayerVisit() { return _isVisited; }

	virtual vector<tagShowNpc> getNpcInfos();

	void moveToIndex(Vector2 index);
	void nextStage();
	void setShowPlayer(bool showPlayer);

	void activeBossUI(bool active);
	void setBossUIHp(int maxHp, int currHp);

	void makeR2REvent(COLORREF color, float time);
	void makeTimeRatioEvent(float ratio, float time);

};