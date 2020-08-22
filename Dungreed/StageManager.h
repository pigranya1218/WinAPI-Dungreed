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
	
	STAGE_TYPE _currStageType; // ���� �������� Ÿ��
	vector<vector<Stage*>> _stageMap;
	Stage* _currStage; // ���� �������� 
	
	int _currIndexX, _currIndexY; // ���� �������� �ε���
	int _mapSize; // ��ü ���� ũ��

private:
	struct tagRoomInfo
	{
		bool isVisited;

		int roomType; // ���� Ÿ�� , -1 : ������� �ʴ� ��, 0 : �Ϲݹ�, 1 : ���۹�, 2: ���� , 3 : �Ĵ��, 4 : ������ 
		bool isWall[4]; // ���� ��, (L T R B) ����
	};

private:
	//���� �������� �����
	vector<Stage*> _bossRoomInfo;
	void makeBossStage();

	vector<vector<tagRoomInfo>> _roomInfo;
	//���� �������� �����
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

	// �������� �� ���� ����
	bool attack(FloatRect* rect, AttackInfo* info);
	bool attack(FloatCircle* circle, AttackInfo* info);
	void attack(Projectile* projectile, AttackInfo* info);

	// �������� �� �浹 ó�� �� �̵�
	void moveTo(GameObject* object, Vector2 moveDir);

	// �������� Ÿ�� �̵�
	void nextStage();

	// �������� �̵� 
	void moveRoom(Vector2 moveDir);
	void moveRoomIndex(Vector2 index);

	// �������� Ÿ�Կ� ���� �� �����
	void makeStage();

	// �������� ����
	// void releaseStage();

	// �÷��̾� ���� �Լ�
	Vector2 getPlayerPos();
	void setPlayerPos(int x, int y);
	Vector2 getEnemyPos(Vector2 pos);

	

	void showDamage(DamageInfo info, Vector2 pos);
	void showEnemyHp(float maxHp, float curHp, Vector2 pos);
};