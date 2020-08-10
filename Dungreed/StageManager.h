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
	STAGE_TYPE _currStageType; // ���� �������� Ÿ��
	vector<Stage*> _stages; // ���� ����������
	Stage* _currStage; // ���� ��������


public:
	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; }

	void init();
	void release();
	void update(float const elapsedTime);
	void render();

	// �������� Ÿ�� �̵�
	void nextStage();

	// �������� �̵� 


	// �������� Ÿ�Կ� ���� �� �����
	void makeStage();

	// �������� ����
	void releaseStage();
};

