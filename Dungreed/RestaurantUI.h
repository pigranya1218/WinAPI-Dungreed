#pragma once

class Player;

class RestaurantUI
{
private:
	Player* _player;

	bool _isActive;

	// *���Ǵ� �̹���
	// ** ���� �޹��

	// ** ��� npc������ ��
	Image* _baseLabel = IMAGE_MANAGER->findImage("UI/RESTAURANT/BASE_LABEL");
	// ** ���� ���� ü�� ������ 
	Image* _lifeBase = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE");
	// ** ü�°����� �޹��
	Image* _lifeBaseBack = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE_BACK");
	// ** ������ ������
	Image* _satietyBase = IMAGE_MANAGER->findImage("UI/RESTAURANT/GAUGE_BASE");
	// ** ������ ������ �޹��
	Image* _satietyBaseBack = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE_BACK");
	// ** ���� �ݾ�
	Image* _goldBase = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE");
	// ** ���� �ݾ� �޹��
	Image* _goldBaseBack = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE_BACK");
	// ** ��� ������
	Image* _goldIcon = IMAGE_MANAGER->findImage("UI/RESTAURANT/GOLD_ICON");
	// ** ������ ������
	Image* _satietyIcon = IMAGE_MANAGER->findImage("UI/RESTAURANT/SATIETY_ICON");
	// ** �� ������
	Image* _healIcon = IMAGE_MANAGER->findImage("UI/RESTAURANT/HEAL_ICON");
	// ** ���� ��� �� 
	//Image* _foodListView = IMAGE_MANAGER->findImage();
	// ** â�ݱ�
	Image* _exitBtn = IMAGE_MANAGER->findImage("BUTTON_EXIT");
	Image* _exitBtnSelected = IMAGE_MANAGER->findImage("BUTTON_EXIT_SELECTED");
	// â�ݱ� ��ư ��Ʈ
	FloatRect _exitRc;
	// ���� ���â ��Ʈ
	FloatRect _foodListViewRc;
private:
	//���� ���
	struct tagFoodsCell
	{

	};
	struct tagScrollBar
	{
		float totalHeight;
		float height;
		float ratio;
		FloatRect bgRc;
		FloatRect scrollRc;
	};

public:
	void setPlayer(Player* player) { _player = player; }

	void init();
	void release();
	void update(float elapsedTime);
	void render();

	bool isActive() const noexcept { return _isActive; }
	void setActive(bool active) { _isActive = active; }
};

