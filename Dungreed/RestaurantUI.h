#pragma once
#include "Food.h"

class Player;
class PlayerStat;

class RestaurantUI
{
private:
	//���� ����Ʈ�� �׸� ��
	struct tagFoodItems
	{
		FloatRect baseRc;
		FloatRect detailsRc;
		
		bool isSoldOut;	//���� ����
	};
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
	Animation* _tableAni;
	Animation* _currHpAni;

	vector<Food*>		_foods;
	Image* _foodImg;

	bool _isActive;
	

	// *���Ǵ� �̹���
	// ** ��� npc������ ��
	Image* _baseLabel = IMAGE_MANAGER->findImage("UI/RESTAURANT/BASE_LABEL");
	// ** ���� ���� ü�� ������ ������
	Image* _lifeBase = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE");
	// ** ü�°����� �޹��
	Image* _lifeBaseBack = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE_BACK");
	// ** ���� ü�� ������ (fill Image)
	Image* _currLifeGauge = IMAGE_MANAGER->findImage("UI/PLAYER_LIFE_BAR");
	// ** ���� ü�� ������ ���̺� 
	Image* _currLifeGaugeWave = IMAGE_MANAGER->findImage("UI/PLAYER_LIFE_WAVE");
	// ** ������ ������
	Image* _satietyBase = IMAGE_MANAGER->findImage("UI/RESTAURANT/GAUGE_BASE");
	// ** ������ ������ �޹��
	Image* _satietyBaseBack = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE_BACK");
	// ** ���� �ݾ� ������
	Image* _goldBase = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE");
	// ** ���� �ݾ� �޹��
	Image* _goldBaseBack = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE_BACK");
	// ** ��� ������
	Image* _goldIcon = IMAGE_MANAGER->findImage("UI/RESTAURANT/GOLD_ICON");
	// ** ������ ������
	Image* _satietyIcon = IMAGE_MANAGER->findImage("UI/RESTAURANT/SATIETY_ICON");
	// ** �� ������
	Image* _healIcon = IMAGE_MANAGER->findImage("UI/RESTAURANT/HEAL_ICON");
	// ** ���� ��� �� ���(������)
	Image* _foodListView = IMAGE_MANAGER->findImage("UI/RESTAURANT/BASE");
	// ** ��ũ�ѹ� ���
	Image* _scrollBarBg = IMAGE_MANAGER->findImage("SCROLL_BG");
	// ** ��ũ�ѹ� ���
	Image* _scrollBarHeader = IMAGE_MANAGER->findImage("SCROLL_HEADER");
	// ** ���� �̹��� ��(���� ���̺� ���� ���̴� �̹���) ���
	Image* _foodTableViewBase = IMAGE_MANAGER->findImage("UI/RESTAURANT/BASE2");
	// ** ���̺� ������ �̹���
	Image* _foodTableFrameView = IMAGE_MANAGER->findImage("UI/RESTAURANT/TABLE");
	// ** â�ݱ�
	Image* _exitBtn = IMAGE_MANAGER->findImage("BUTTON_EXIT");
	Image* _exitBtnSelected = IMAGE_MANAGER->findImage("BUTTON_EXIT_SELECTED");
	//// ** ��ũ��
	//Image* _scrollBarBg = IMAGE_MANAGER->findImage("SCROLL_BG");
	//Image* _scrollBarHeader = IMAGE_MANAGER->findImage("SCROLL_HEADER");
	// ** ���� �׸� �� ���
	Image* _foodListItem = IMAGE_MANAGER->findImage("UI/RESTAURANT/MENU"); //���
	Image* _foodListItemSelected = IMAGE_MANAGER->findImage("UI/RESTAURANT/MENU_SELECTED"); //������ ���
	Image* _foodListItemSoldOut = IMAGE_MANAGER->findImage("UI/RESTAURANT/THANKYOU_KR");

	// * ���Ǵ� ��Ʈ
	// �޹�� fillRectangle -> ����RGB(34, 32, 52)
	FloatRect _bgRc;
	// ����Ʈ �׸��� ���ٵǴ� �� �����ֱ� ���� �޹��
	FloatRect _bgRc2;
	// â�ݱ� ��ư ��Ʈ
	FloatRect _exitRc;
	// ���� ���â ��Ʈ
	FloatRect _foodListViewRc;
	// ���� �̹��� â ��Ʈ
	FloatRect _foodTableViewRc;
	// ������ ������ ��Ʈ
	FloatRect _satietyRc;
	// ���� �������� ��ĥ�� ��Ʈ
	FloatRect _currSatietyRateFillRc;
	// ������ value�� ǥ���� ��Ʈ
	FloatRect _satietyRateRc;
	// ���� ü�� ������ ��Ʈ
	FloatRect _lifeGaugeRc;
	// ���� �ݾ� ��Ʈ
	FloatRect _goldBaseRc;
	// �ݾ� ���� �ؽ�Ʈ ������ ��Ʈ
	FloatRect _goldAmountRc;
	// ��� ������ ��Ʈ
	FloatRect _goldIconRc;
	
	tagFoodItems _foodItems[5];
	tagScrollBar _scrollBar;
	

public:
	void setPlayer(Player* player) { _player = player; }

	void init();
	void release();
	void update(float elapsedTime);
	void render();

	bool isActive() const noexcept { return _isActive; }
	void setActive(bool active) { _isActive = active; }
};

