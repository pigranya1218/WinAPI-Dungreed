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
	typedef vector<Stage*> VStage;

	GameScene* _gameScene;
	Player* _player;
	UIManager* _uiMgr;
	STAGE_TYPE _currStageType; // 현재 스테이지 타입
	vector<Stage*> _stages; // 현재 스테이지들
	Stage* _currStage; // 현재 스테이지 
	
	Stage* _downStair;
	Stage* _restaurantRoom;
	Stage* _shopRoom;

	int _roomIndex;
	vector<VStage> _vStage;
	vector<DIRECTION>::iterator iter;
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

	void showDamage(DamageInfo info, Vector2 pos);
	void showEnemyHp(float maxHp, float curHp, Vector2 pos);
};

