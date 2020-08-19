#pragma once

#include "Stage.h"
#include "Projectile.h"

class GameScene;
class Player;

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
	STAGE_TYPE _currStageType; // 현재 스테이지 타입
	vector<Stage*> _stages; // 현재 스테이지들
	Stage* _currStage; // 현재 스테이지 
	
	Stage* _stage;
	Stage* _stage2;

	Stage* _downStair;
	Stage* _restaurantRoom;
	Stage* _shopRoom;

	int _roomIndex;
	int _currIndexX, _currIndexY;

	int k;
	int l;
	
	vector<vector<Stage*>> _vStage;
	vector<DIRECTION>::iterator iter;

	int rnd;
public:
	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; }
	void setPlayer(Player* player) { _player = player; }
	void setStageType(STAGE_TYPE currStageType) { _currStageType = currStageType; }

	void init();
	void release();
	void update(float const elapsedTime);
	void render();

	// 스테이지 내 공격 판정
	void attack(FloatRect* rect, AttackInfo* info);
	void attack(FloatCircle* circle, AttackInfo* info);
	void attack(Projectile* projectile, AttackInfo* info);

	// 스테이지 내 충돌 처리 및 이동
	void moveTo(GameObject* object, Vector2 moveDir);

	// 스테이지 타입 이동
	void nextStage();

	// 스테이지 이동 
	void moveRoom();

	// 스테이지 타입에 따른 맵 만들기
	void makeStage();

	// 스테이지 해제
	void releaseStage();

	// 플레이어 관련 함수
	Vector2 getPlayerPos();
	void setPlayerPos(int x, int y);

	//랜덤맵만들기
	void makeRoom(int x1, int y1, vector<bool> isMadeSpecial, vector<vector<bool>> isMadeRoom);
};

