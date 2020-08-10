#pragma once

class Stage;
class GameScene;

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
	STAGE_TYPE _currStageType; // 현재 스테이지 타입
	vector<Stage*> _stages; // 현재 스테이지들
	Stage* _currStage; // 현재 스테이지


public:
	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; }

	void init();
	void release();
	void update(float const elapsedTime);
	void render();

	// 스테이지 타입 이동
	void nextStage();

	// 스테이지 이동 


	// 스테이지 타입에 따른 맵 만들기
	void makeStage();

	// 스테이지 해제
	void releaseStage();
};

