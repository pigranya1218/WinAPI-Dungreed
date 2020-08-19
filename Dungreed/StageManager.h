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
	STAGE_TYPE _currStageType; // ���� �������� Ÿ��
	vector<Stage*> _stages; // ���� ����������
	Stage* _currStage; // ���� �������� 
	
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

	// �������� �� ���� ����
	void attack(FloatRect* rect, AttackInfo* info);
	void attack(FloatCircle* circle, AttackInfo* info);
	void attack(Projectile* projectile, AttackInfo* info);

	// �������� �� �浹 ó�� �� �̵�
	void moveTo(GameObject* object, Vector2 moveDir);

	// �������� Ÿ�� �̵�
	void nextStage();

	// �������� �̵� 
	void moveRoom();

	// �������� Ÿ�Կ� ���� �� �����
	void makeStage();

	// �������� ����
	void releaseStage();

	// �÷��̾� ���� �Լ�
	Vector2 getPlayerPos();
	void setPlayerPos(int x, int y);

	//�����ʸ����
	void makeRoom(int x1, int y1, vector<bool> isMadeSpecial, vector<vector<bool>> isMadeRoom);
};

