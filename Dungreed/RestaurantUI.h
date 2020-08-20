#pragma once
#include "Food.h"

class Player;
class PlayerStat;

class RestaurantUI
{
private:
	//음식 리스트의 항목 셀
	struct tagFoodItems
	{
		FloatRect baseRc;
		FloatRect detailsRc;
		
		bool isSoldOut;	//구매 여부
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
	

	// *사용되는 이미지
	// ** 상단 npc아이콘 띠
	Image* _baseLabel = IMAGE_MANAGER->findImage("UI/RESTAURANT/BASE_LABEL");
	// ** 현재 남은 체력 게이지 프레임
	Image* _lifeBase = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE");
	// ** 체력게이지 뒷배경
	Image* _lifeBaseBack = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE_BACK");
	// ** 현재 체력 게이지 (fill Image)
	Image* _currLifeGauge = IMAGE_MANAGER->findImage("UI/PLAYER_LIFE_BAR");
	// ** 현재 체력 게이지 웨이브 
	Image* _currLifeGaugeWave = IMAGE_MANAGER->findImage("UI/PLAYER_LIFE_WAVE");
	// ** 포만감 게이지
	Image* _satietyBase = IMAGE_MANAGER->findImage("UI/RESTAURANT/GAUGE_BASE");
	// ** 포만감 게이지 뒷배경
	Image* _satietyBaseBack = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE_BACK");
	// ** 현재 금액 프레임
	Image* _goldBase = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE");
	// ** 현재 금액 뒷배경
	Image* _goldBaseBack = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE_BACK");
	// ** 골드 아이콘
	Image* _goldIcon = IMAGE_MANAGER->findImage("UI/RESTAURANT/GOLD_ICON");
	// ** 포만감 아이콘
	Image* _satietyIcon = IMAGE_MANAGER->findImage("UI/RESTAURANT/SATIETY_ICON");
	// ** 힐 아이콘
	Image* _healIcon = IMAGE_MANAGER->findImage("UI/RESTAURANT/HEAL_ICON");
	// ** 음식 목록 뷰 배경(프레임)
	Image* _foodListView = IMAGE_MANAGER->findImage("UI/RESTAURANT/BASE");
	// ** 스크롤바 배경
	Image* _scrollBarBg = IMAGE_MANAGER->findImage("SCROLL_BG");
	// ** 스크롤바 헤더
	Image* _scrollBarHeader = IMAGE_MANAGER->findImage("SCROLL_HEADER");
	// ** 음식 이미지 뷰(대충 테이블에 음식 놓이는 이미지) 배경
	Image* _foodTableViewBase = IMAGE_MANAGER->findImage("UI/RESTAURANT/BASE2");
	// ** 테이블 프레임 이미지
	Image* _foodTableFrameView = IMAGE_MANAGER->findImage("UI/RESTAURANT/TABLE");
	// ** 창닫기
	Image* _exitBtn = IMAGE_MANAGER->findImage("BUTTON_EXIT");
	Image* _exitBtnSelected = IMAGE_MANAGER->findImage("BUTTON_EXIT_SELECTED");
	//// ** 스크롤
	//Image* _scrollBarBg = IMAGE_MANAGER->findImage("SCROLL_BG");
	//Image* _scrollBarHeader = IMAGE_MANAGER->findImage("SCROLL_HEADER");
	// ** 음식 항목 셀 배경
	Image* _foodListItem = IMAGE_MANAGER->findImage("UI/RESTAURANT/MENU"); //배경
	Image* _foodListItemSelected = IMAGE_MANAGER->findImage("UI/RESTAURANT/MENU_SELECTED"); //선택중 배경
	Image* _foodListItemSoldOut = IMAGE_MANAGER->findImage("UI/RESTAURANT/THANKYOU_KR");

	// * 사용되는 렉트
	// 뒷배경 fillRectangle -> 색상RGB(34, 32, 52)
	FloatRect _bgRc;
	// 리스트 항목이 오바되는 걸 가려주기 위한 뒷배경
	FloatRect _bgRc2;
	// 창닫기 버튼 렉트
	FloatRect _exitRc;
	// 음식 목록창 렉트
	FloatRect _foodListViewRc;
	// 음식 이미지 창 렉트
	FloatRect _foodTableViewRc;
	// 포만률 게이지 렉트
	FloatRect _satietyRc;
	// 현재 포만률을 색칠할 렉트
	FloatRect _currSatietyRateFillRc;
	// 포만률 value를 표시할 렉트
	FloatRect _satietyRateRc;
	// 현재 체력 게이지 렉트
	FloatRect _lifeGaugeRc;
	// 현재 금액 렉트
	FloatRect _goldBaseRc;
	// 금액 적을 텍스트 렌더용 렉트
	FloatRect _goldAmountRc;
	// 골드 아이콘 렉트
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

