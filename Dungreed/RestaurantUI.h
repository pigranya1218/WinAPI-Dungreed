#pragma once

class Player;

class RestaurantUI
{
private:
	Player* _player;
	Animation* _tableAni;

	bool _isActive;

	// *사용되는 이미지
	// ** 상단 npc아이콘 띠
	Image* _baseLabel = IMAGE_MANAGER->findImage("UI/RESTAURANT/BASE_LABEL");
	// ** 현재 남은 체력 게이지 
	Image* _lifeBase = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE");
	// ** 체력게이지 뒷배경
	Image* _lifeBaseBack = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE_BACK");
	// ** 포만감 게이지
	Image* _satietyBase = IMAGE_MANAGER->findImage("UI/RESTAURANT/GAUGE_BASE");
	// ** 포만감 게이지 뒷배경
	Image* _satietyBaseBack = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE_BACK");
	// ** 현재 금액
	Image* _goldBase = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE");
	// ** 현재 금액 뒷배경
	Image* _goldBaseBack = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE_BACK");
	// ** 골드 아이콘
	Image* _goldIcon = IMAGE_MANAGER->findImage("UI/RESTAURANT/GOLD_ICON");
	// ** 포만감 아이콘
	Image* _satietyIcon = IMAGE_MANAGER->findImage("UI/RESTAURANT/SATIETY_ICON");
	// ** 힐 아이콘
	Image* _healIcon = IMAGE_MANAGER->findImage("UI/RESTAURANT/HEAL_ICON");
	// ** 음식 목록 뷰 배경
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
	
	// * 사용되는 렉트
	// 뒷배경 fillRectangle -> 색상RGB(34, 32, 52)
	FloatRect _bgRc;
	// 창닫기 버튼 렉트
	FloatRect _exitRc;
	// 음식 목록창 렉트
	FloatRect _foodListViewRc;
	// 음식 이미지 창 렉트
	FloatRect _foodTableViewRc;
	// 포만감 게이지 렉트
	FloatRect _satietyRc;
	// 현재 체력 게이지 렉트
	FloatRect _lifeGaugeRc;
	// 현재 금액 렉트
	FloatRect _goldBaseRc;
	// 금액 적을 텍스트 렌더용 렉트
	FloatRect _goldAmountRc;
	// 골드 아이콘 렉트
	FloatRect _goldIconRc;
	// 스크롤 렉트
	FloatRect _scrollBarBgRc;
	FloatRect _scrollBarHeaderRc;
	
private:
	//음식 목록
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

