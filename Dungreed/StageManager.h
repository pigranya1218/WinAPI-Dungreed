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
	

public:
	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; }
	void setPlayer(Player* player) { _player = player; }

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


	// �������� Ÿ�Կ� ���� �� �����
	void makeStage();

	// �������� ����
	void releaseStage();

	// �÷��̾� ���� �Լ�
	Vector2 getPlayerPos();
};

