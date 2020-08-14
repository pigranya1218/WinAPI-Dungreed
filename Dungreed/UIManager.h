#pragma once
#include "InventoryUI.h"
#include "StatUI.h"
#include "CostumeUI.h"

class GameScene;
class Player;
class StageManager;

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

	struct tagSkillUI // ���� ��ų
	{

	};

	struct tagMiniMap // �̴ϸ�
	{
		FloatRect miniMapRc;
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
	InventoryUI _inventoryUI;
	StatUI _statUI;
	CostumeUI _costumeUI;


public:
	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; }
	void setPlayer(Player* player);
	void setStageManager(StageManager* stageMgr) { _stageMgr = stageMgr; }

	void init();
	void release();
	void update(float const elaspedTime);
	void render();

	bool isActive() const noexcept { return _isActive; }
};

