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
	STAGE_TYPE _currStageType; // ���� �������� Ÿ��
	vector<Stage*> _stages; // ���� ����������
	Stage* _currStage; // ���� �������� 
	
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

	void showDamage(DamageInfo info, Vector2 pos);
	void showEnemyHp(float maxHp, float curHp, Vector2 pos);
};

