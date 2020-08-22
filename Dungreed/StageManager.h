#pragma once

#include "Stage.h"
#include "Projectile.h"

class GameScene;
class Player;
class UIManager;

enum class STAGE_TYPE : int
{
	VILLAGE = 0,
	DUNGEON_NORMAL,
	DUNGEON_BOSS,
	TEST
};

class StageManager
{
private:
	GameScene* _gameScene;
	Player* _player;
	UIManager* _uiMgr;
	
	STAGE_TYPE _currStageType; // 현재 스테이지 타입
	vector<vector<Stage*>> _stageMap;
	Stage* _currStage; // 현재 스테이지 
	
	int _currIndexX, _currIndexY; // 현재 스테이지 인덱스
	int _mapSize; // 전체 맵의 크기

private:
	struct tagRoomInfo
	{
		bool isVisited;

		int roomType; // 방의 타입 , -1 : 사용하지 않는 방, 0 : 일반방, 1 : 시작방, 2: 끝방 , 3 : 식당방, 4 : 상점방 
		bool isWall[4]; // 방의 벽, (L T R B) 순서
	};

private:
	//보스 스테이지 만들기
	vector<Stage*> _bossRoomInfo;
	void makeBossStage();

	vector<vector<tagRoomInfo>> _roomInfo;
	//랜덤 스테이지 만들기
	void makeDungeon();
	void makeRoom(int x, int y);
	bool makeSpecialRoom();
	void releaseStage();
	Stage* getStage(int stageType, bool isWall[]);
	string getStageTitle();

public:
	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; }
	void setPlayer(Player* player) { _player = player; }
	void setUIManager(UIManager* uiMgr) { _uiMgr = uiMgr; }
	void setStageType(STAGE_TYPE currStageType) { _currStageType = currStageType; }

	void init();
	void release();
	void update(float const elapsedTime);
	void render();

	// 스테이지 내 공격 판정
	bool attack(FloatRect* rect, AttackInfo* info);
	bool attack(FloatCircle* circle, AttackInfo* info);
	void attack(Projectile* projectile, AttackInfo* info);

	// 스테이지 내 충돌 처리 및 이동
	void moveTo(GameObject* object, Vector2 moveDir);

	// 스테이지 타입 이동
	void nextStage();

	// 스테이지 이동 
	void moveRoom(Vector2 moveDir);
	void moveRoomIndex(Vector2 index);

	// 스테이지 타입에 따른 맵 만들기
	void makeStage();

	// 스테이지 해제
	// void releaseStage();

	// 플레이어 관련 함수
	Vector2 getPlayerPos();
	void setPlayerPos(int x, int y);
	Vector2 getEnemyPos(Vector2 pos);

	

	void showDamage(DamageInfo info, Vector2 pos);
	void showEnemyHp(float maxHp, float curHp, Vector2 pos);
};