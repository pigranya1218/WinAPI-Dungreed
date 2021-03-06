#pragma once
#include "PlayerStat.h"
#include "Food.h"

class Player;

class StatUI
{
private:
	struct tagStatUI
	{
		Image* icon;		// ���� ������
		Image* iconSelected;// ���� ������ ����
		FloatRect iconRc;	// ���� ������ ��Ʈ
	};

	//Foods â ����Ʈ ��
	struct tagEatFoods
	{
		FloatRect cellRc;	//����Ʈ �� ��ĭ�� ��Ʈ
		FloatRect num;		//������ ���� ����
	};

	//Foods â ��ũ�� ��
	struct tagScrollBar
	{
		float totalHeight;
		float height;
		float ratio;
		FloatRect bgRc;
		FloatRect scrollRc;
	};
private:
	Player* _player;
	PlayerStat* _playerStat;

	bool _isActive;

	Image*		_statBaseImg;	// ����â ���� �̹���
	FloatRect	_statBaseRc;	// ����â ���� ��Ʈ
	Image*		_foodBaseImg;	// Ǫ��â ���� �̹���
	FloatRect	_foodBaseRc;	// Ǫ��â ���� ��Ʈ
	Image*		_foodListCellFrameImg; // Ǫ��â ����Ʈ �� ��ĭ ������ �̹���
	Image*		_foodListCellBackImg; // Ǫ��â ����Ʈ �� ��ĭ �޹�� �̹���
	Image*		_exitImg;		// â�ݱ� �̹���
	Image*		_exitSelectImg;	// â�ݱ� ���� �̹���
	FloatRect	_exitRc;		// â�ݱ� ��Ʈ
	tagStatUI _statEntity[12];

private:
	vector<Food*>			_foods;		//���� ���� ������ ����
	vector<Food*>::iterator	_viFoods;	//���� �Ǵ� ������ �̹� �Ծ��� ���İ� ���� ������ �ִ��� �˻��ϱ� ���� �ݺ���
	tagEatFoods				_foodList[10];	//���� ����Ʈ ���� �迭�� ����

public:
	void setPlayer(Player* player) { _player = player; }

	void init();
	void release();
	void update(float elapsedTime);
	void render();

	bool isActive() const noexcept { return _isActive; }
	void setActive(bool active) { _isActive = active; }
	void renderStatInfo(Vector2 pos, STAT_TYPE type);

	void setEatFoods(Food* food); //���� ���� ���� ���� ��
};

