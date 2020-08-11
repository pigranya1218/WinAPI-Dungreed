#pragma once

class  GameScene;
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

		Image* dashBgImg;
		Image* dashFgImg;
		FloatRect dashBg; // �뽬 ���
		FloatRect dashFg; // �뽬 ������
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
		FloatRect currRc;
		FloatRect swapRc;
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

public:
	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; }
	void setPlayer(Player* player) { _player = player; }
	void setStageManager(StageManager* stageMgr) { _stageMgr = stageMgr; }

	void init();
	void release();
	void update(float const elaspedTime);
	void render();

	bool isActive() const noexcept { return _isActive; }
};

