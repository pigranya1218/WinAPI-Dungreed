#pragma once
#include "PlayerStat.h"
#include "Food.h"

class Player;

class StatUI
{
private:
	struct tagStatUI
	{
		Image* icon;		// 스탯 아이콘
		Image* iconSelected;// 스탯 아이콘 선택
		FloatRect iconRc;	// 스탯 아이콘 렉트
	};

	//Foods 창 리스트 셀
	struct tagEatFoods
	{
		FloatRect cellRc;	//리스트 셀 한칸의 렉트
		FloatRect num;		//음식을 먹은 개수
	};

	//Foods 창 스크롤 바
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

	Image*		_statBaseImg;	// 스탯창 바탕 이미지
	FloatRect	_statBaseRc;	// 스탯창 바탕 렉트
	Image*		_foodBaseImg;	// 푸드창 바탕 이미지
	FloatRect	_foodBaseRc;	// 푸드창 바탕 렉트
	Image*		_foodListCellFrameImg; // 푸드창 리스트 셀 한칸 프레임 이미지
	Image*		_foodListCellBackImg; // 푸드창 리스트 셀 한칸 뒷배경 이미지
	Image*		_exitImg;		// 창닫기 이미지
	Image*		_exitSelectImg;	// 창닫기 선택 이미지
	FloatRect	_exitRc;		// 창닫기 렉트
	tagStatUI _statEntity[12];

private:
	vector<Food*>			_foods;		//먹은 음식 정보를 저장
	vector<Food*>::iterator	_viFoods;	//삽입 되는 음식이 이미 먹었던 음식과 같은 종류가 있는지 검사하기 위한 반복자
	tagEatFoods				_foodList[10];	//음식 리스트 셀을 배열로 저장

public:
	void setPlayer(Player* player) { _player = player; }

	void init();
	void release();
	void update(float elapsedTime);
	void render();

	bool isActive() const noexcept { return _isActive; }
	void setActive(bool active) { _isActive = active; }
	void renderStatInfo(Vector2 pos, STAT_TYPE type);

	void setEatFoods(Food* food); //먹은 음식 전달 받을 것
};

