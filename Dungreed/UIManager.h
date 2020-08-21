#pragma once
#include "InventoryUI.h"
#include "StatUI.h"
#include "CostumeUI.h"
#include "RestaurantUI.h"
#include "DialogueUI.h"
#include "DamageInfo.h"
#include "LinearFunc.h"
#include "DoorObject.h"

class GameScene;
class Player;
class StageManager;
class EnemyManager;
class NpcManager;
class ObjectManager;

class UIManager
{
private:
	struct tagPlayerUI // �÷��̾� hp, �뽬ī��Ʈ, ����
	{
		Image* hpBgImg; // hp�� ���
		Image* hpFrameImg; // hp�� ������
		Image* hpBarImg; // hp�� ������
		Image* hpWaveImg; // hp�� ���̺�
		
		FloatRect hpBg; // hp�� ���
		FloatRect hpBar; // hp�� ������
		FloatRect hpLevel; // ���� 
		
		Animation* hpAni; // hp�� ���ϸ��̼�

		FloatRect levelRc; // ���� ����

		Image* dashOutsideImg;
		Image* dashInsideImg;
		Image* dashGaugeImg;
		Vector2 dashFirstCenter;
	};

	struct tagLabelUI // �̹��� + �� (���, ������, ��������, �����̵�)
	{
		Image* img;
		Animation* ani;
		FloatRect imgRc;
		FloatRect textRc;
		int fontSize;
	};

	struct tagProgressUI
	{
		FloatRect progressRc;
	};

	struct tagWeaponUI // ���� ������ �����
	{
		Image* bgImg;
		Vector2 frontBaseCenter;
		Vector2 backBaseCenter;
		FloatRect frontIndexRc;
		FloatRect frontBulletRc;
		
		float moveSpeed;
		int viewIndex;
		Vector2 move;
	};

	struct tagDamageUI // ������� ���� ���� ǥ��
	{
		int type; // 0 = damage, 1 = EVADE, 2 = BLOCK
		float value; // ����� ��
		COLORREF textColor;
		float remainTimes; // ���������� ���� �ð�
		float fontSize; // ���� ũ��, ũ��Ƽ���̳Ŀ� ���� �ٸ�
		Vector2 pos; // �׸� ��ġ
		float alpha;
	};

	struct tagEnemyHpUI // ���ʹ� ü��
	{
		float maxHp;
		float currHp;
		Vector2 pos; // �׸� ��ġ
	};

	struct tagMiniMap // �̴ϸ�
	{
		vector<FloatRect> collisionRect; // �̴ϸʿ� �׷��� ��
		vector<FloatRect> doorRect; // �̴ϸʿ� �׷��� ��
		EnemyManager* enemyMgr;
		NpcManager* npcMgr;
		ObjectManager* objectMgr;
	};
private:
	GameScene* _gameScene;
	Player* _player;
	StageManager* _stageMgr;

	bool _isActive; // â�� �� ���

	tagPlayerUI _hpUI; // �÷��̾� HP
	tagLabelUI	_goldUI; // �÷��̾� ������ ��
	tagLabelUI	_satietyUI; // �÷��̾� ������ ��
	tagProgressUI	_satietyProgress; // �÷��̾� ������ ���α׷�����
	tagWeaponUI	_weaponUI; // ���� UI
	tagMiniMap _mapUI; // �̴ϸ� UI

	vector<tagDamageUI> _damageUI; // ����� ǥ�� ���� UI
	vector<tagEnemyHpUI> _enemyHpUI; // �� ü�¹� UI

	DialogueUI _dialogueUI;
	InventoryUI _inventoryUI;
	StatUI _statUI;
	CostumeUI _costumeUI;
	RestaurantUI _restaurantUI;

public:
	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; }
	void setPlayer(Player* player);
	void setStageManager(StageManager* stageMgr) { _stageMgr = stageMgr; }

	void init();
	void release();
	void update(float const elaspedTime);
	void render();

	void setMap(vector<FloatRect> groundRect, vector<LinearFunc> groundLine, vector<LinearFunc> platformLine, vector<DoorObject*> doors, EnemyManager* enemyManager, NpcManager* npcManager, ObjectManager* objectManager);

	bool isActive() const noexcept { return _isActive; }

	void showDamage(DamageInfo damage, Vector2 pos);
	void showEnemyHp(float maxHp, float curHp, Vector2 pos);

	void setDialogue(Npc* npc) { _dialogueUI.startDialogue(npc); }
};

