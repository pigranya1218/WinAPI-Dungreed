#include "stdafx.h"
#include "RestaurantUI.h"
#include "BreadFood.h"
#include "EggFriedFood.h"
#include "GrilledMushroomFood.h"
#include "TomatoSoupFood.h"
#include "GriffinEggOmeletteFood.h"
#include "RaspberryCookieFood.h"
#include "SparklingWaterFood.h"
#include "StrawberryPieFood.h"
#include "Player.h"
#include "PlayerStat.h"
//#include "StatUI.h"

void RestaurantUI::init()
{
	//FOODS 리스트 벡터에 FOOD* 클래스 삽입
	/*for (int i = 0; i < 5; i++)
	{
		_foods.push_back(new EggFriedFood);
	}*/
	_foods.push_back(new BreadFood);
	_foods.push_back(new EggFriedFood);
	_foods.push_back(new GrilledMushroomFood);
	_foods.push_back(new TomatoSoupFood);
	_foods.push_back(new GriffinEggOmeletteFood);
	_foods.push_back(new RaspberryCookieFood);
	_foods.push_back(new SparklingWaterFood);
	_foods.push_back(new StrawberryPieFood);
	

	_isActive = false;
	//전체 뒷배경
	//_bgRc = FloatRect(Vector2(WINSIZEX / 2, WINSIZEY / 2), Vector2(WINSIZEX, WINSIZEY));
	_bgRc = FloatRect(0, 0, WINSIZEX, WINSIZEY);
	_bgRc2 = FloatRect(0, 780, 500, WINSIZEY);
	//창닫기 버튼
	_exitRc = FloatRect(WINSIZEX - 150, 40, WINSIZEX - 30, 130);
	//음식 목록 창
	_foodListViewRc = FloatRect(20, 180, 500, 780);
	//포만감 게이지 배경
	_satietyRc = FloatRect(15, 800, 515, 880);
	//포만률 게이지 색칠할 렉트
	//_currSatietyRateFillRc = FloatRect(140, 800, 141, 880);
	//포만률 값을 표시할 렉트
	_satietyRateRc = FloatRect(140, 800, 515, 880);
	//음식 이미지 창(테이블)
	_foodTableViewRc = FloatRect(550, 180, WINSIZEX - 20, 780);
	//체력 게이지 창
	_lifeGaugeRc = FloatRect(570, 200, 870, 300);
	//스크롤
	//_scrollBarBgRc = FloatRect(510, 180, 540, 780);
	//금액 창
	_goldBaseRc = FloatRect(1400, 800, WINSIZEX - 20, 880);
	//금액 텍스트 렌더용 렉트
	_goldAmountRc = FloatRect(1410, 800, WINSIZEX - 80, 880);
	//골드 아이콘 렉트
	_goldIconRc = FloatRect(WINSIZEX - 80, 800, WINSIZEX - 20, 880);

	//음식 리스트 항목 창
	for (int i = 0; i < 5; i++)
	{
		_foodItems[i].isSoldOut = false;
		//가로 440, 세로 200
		if(i == 0) _foodItems[i].baseRc = FloatRect(_foodListViewRc.left + 20, _foodListViewRc.top + 20, _foodListViewRc.right - 20, _foodListViewRc.top + 220);
		else _foodItems[i].baseRc = FloatRect(_foodItems[i - 1].baseRc.left, _foodItems[i - 1].baseRc.bottom + 5, _foodItems[i - 1].baseRc.right, _foodItems[i-1].baseRc.bottom + 205);
	}

	//테이블 이미지 애니메이션
	_tableAni = new Animation;
	_tableAni->init(_foodTableFrameView->getWidth(), _foodTableFrameView->getHeight(), _foodTableFrameView->getMaxFrameX(), _foodTableFrameView->getMaxFrameY());
	_tableAni->setPlayFrame(0, _foodTableFrameView->getMaxFrameX(), false, true);
	_tableAni->setFPS(10);
	_tableAni->start();

	//HP게이지 웨이브 애니메이션
	_currHpAni = new Animation;
	_currHpAni->init(_currLifeGaugeWave->getWidth(), _currLifeGaugeWave->getHeight(), _currLifeGaugeWave->getMaxFrameX(), _currLifeGaugeWave->getMaxFrameY());
	_currHpAni->setFPS(15);
	_currHpAni->setDefPlayFrame(false, true);
	_currHpAni->start();

	//스크롤 바
	_scrollBar.totalHeight = (_foodItems[0].baseRc.getHeight() + 5) * _foods.size() + 35;
	_scrollBar.height = _foodListViewRc.getHeight();
	_scrollBar.ratio = 0;
	_scrollBar.bgRc = FloatRect(510, 180, 540, 780);
	_scrollBar.scrollRc = FloatRect(510.0, 180.0, 540.0, (_scrollBar.height / _scrollBar.totalHeight) * (_scrollBar.bgRc.bottom - _scrollBar.bgRc.top));
	_isScroll = false;
	_lastPtMouse = _ptMouse;
	//float offsetY = -100; // 스크롤을 아래로 땡긴 만큼 어떠한 값이 될 것
	// 맨 처음 스크롤이 맨 위에 있을 땐 0
}

void RestaurantUI::release()
{
	_tableAni->release();
	delete _tableAni;
}

void RestaurantUI::update(float elapsedTime)
{
	_tableAni->frameUpdate(elapsedTime);
	_currHpAni->frameUpdate(elapsedTime);

	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//창닫기
		if (_exitRc.ptInRect(_ptMouse))
		{
			_isActive = false;
		}
		//스크롤바 드래그
		if (_scrollBar.scrollRc.ptInRect(_ptMouse))
		{
			_isScroll = true;
		}

	}
	if (KEY_MANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		//음식 구매
		for (int i = 0; i < _foods.size(); i++)
		{
			int offsetY = -(_scrollBar.ratio * (_scrollBar.totalHeight - _scrollBar.height));
			FloatRect relativeRc = _foodItems[i].baseRc;
			relativeRc.top += offsetY;
			relativeRc.bottom += offsetY;

			if (relativeRc.ptInRect(_ptMouse) && _foodListViewRc.top < _ptMouse.y && _foodListViewRc.bottom > _ptMouse.y)
			{
				if (_player->ateFood(_foods[i]))
				{
					_foodItems[i].isSoldOut = true;
					
				}
			}
		}
	}

	if (_isScroll)
	{
		Vector2 currCenter = _scrollBar.scrollRc.getCenter();
		int move = _ptMouse.y - _lastPtMouse.y;
		currCenter.y += move;
		currCenter.y = min(currCenter.y, _scrollBar.bgRc.bottom - (_scrollBar.scrollRc.getSize().y / 2));
		currCenter.y = max(currCenter.y, _scrollBar.bgRc.top + (_scrollBar.scrollRc.getSize().y / 2));
		_scrollBar.scrollRc = FloatRect(currCenter, _scrollBar.scrollRc.getSize(), PIVOT::CENTER);
		_scrollBar.ratio = (currCenter.y - (_scrollBar.bgRc.top + (_scrollBar.scrollRc.getSize().y / 2)))
			/ ((_scrollBar.bgRc.bottom - (_scrollBar.scrollRc.getSize().y / 2)) - (_scrollBar.bgRc.top + (_scrollBar.scrollRc.getSize().y / 2)));
		CAMERA->setT((_scrollBar.totalHeight - _scrollBar.height) * _scrollBar.ratio);
	}

	if (KEY_MANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_isScroll = false;
	}
	_lastPtMouse = _ptMouse;
}

void RestaurantUI::render()
{
	//전체 뒷배경
	D2D_RENDERER->fillRectangle(_bgRc, 34, 32, 52, 1);
	
	//테이블 음식 이미지 창
	_foodTableFrameView->aniRender(_foodTableViewRc.getCenter(), _foodTableViewRc.getSize(), _tableAni);
	_foodTableViewBase->render(_foodTableViewRc.getCenter(), _foodTableViewRc.getSize());

	int offsetY = -(_scrollBar.ratio * (_scrollBar.totalHeight - _scrollBar.height));

	//음식 리스트의 항목
	for (int i = 0; i < _foods.size(); i++)
	{
		//FloatRect relativeRc = _foodItems[i].baseRc;
		//relativeRc.top += offsetY;
		//relativeRc.bottom += offsetY;
		FloatRect relativeRc = _foodItems[i].baseRc;
		relativeRc.top += offsetY;
		relativeRc.bottom += offsetY;
		if (relativeRc.ptInRect(_ptMouse) && _foodListViewRc.bottom > _ptMouse.y && _foodListViewRc.top < _ptMouse.y)
		{
			if (!_foodItems[i].isSoldOut)
			{
				_foodListItemSelected->render(relativeRc.getCenter(), relativeRc.getSize());
			}
			_foodImg = _foods[i]->getImage();
			_foodImg->setScale(4.5);
			_foodImg->setAlpha(0.7);
			_foodImg->render(Vector2(_foodTableViewRc.getCenter().x, _foodTableViewRc.getCenter().y + 30));
		}
		else
		{
			_foodListItem->render(relativeRc.getCenter(), relativeRc.getSize());
		}
		if(!_foodItems[i].isSoldOut)
		{ 
			//아이템에 따른 변화되는 스탯 받아오는 작업
			PlayerStat foodAddStat = _foods[i]->getAddStat();
			PlayerStat foodOneceStat = _foods[i]->getOnceStat();
			//food 벡터에 있는 아이템들을 리스트 foodItems에 표시
			FOOD_RANK foodRank = _foods[i]->getRank();
			//int foodRankInt = static_cast<int>(foodRank);
			D2D_RENDERER->renderTextField(relativeRc.left + 20, relativeRc.top, TTYONE_UTIL::stringTOwsting(_foods[i]->getName()),
				((foodRank == FOOD_RANK::RARE) ? RGB(169, 251, 150) : RGB(255, 178, 144)), 40, relativeRc.getWidth(), relativeRc.getHeight() - 150, 1, DWRITE_TEXT_ALIGNMENT_LEADING);
			int addStatCount = 0;
			int oneceStatCount = 0;
			for (int j = 0; j < static_cast<int>(STAT_TYPE::END); j++)
			{
				STAT_TYPE statType = static_cast<STAT_TYPE>(j);
				//영구적으로 변화되는 스탯
				int addStatValue = foodAddStat.getStat(statType);
				string addStatString = foodAddStat.getStatString(statType, false);
				if (addStatValue != 0)
				{
					addStatCount++;
					D2D_RENDERER->renderTextField(relativeRc.left + 15, relativeRc.top + 10 + (40 * addStatCount), L"▶",
						RGB(255, 255, 255), 30, relativeRc.getWidth(), relativeRc.getHeight() - 150, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아");
					D2D_RENDERER->renderTextField(relativeRc.left + 50, relativeRc.top + 10 + (40 * addStatCount), ((addStatValue >= 0) ? (L"+") : (L"")) + to_wstring(addStatValue), (addStatValue >= 0) ? RGB(0, 255, 0) : RGB(255, 0, 0)
						, 30, relativeRc.getWidth(), relativeRc.getHeight() - 150, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아");
					D2D_RENDERER->renderTextField(relativeRc.left + 100, relativeRc.top + 10 + (40 * addStatCount), TTYONE_UTIL::stringTOwsting(addStatString), RGB(255, 255, 255)
						, 30, relativeRc.getWidth(), relativeRc.getHeight() - 150, 1, DWRITE_TEXT_ALIGNMENT_LEADING);
				}
				//렉트 만들기
				FloatRect value[3];	// 회복률, 포만률, 가격의 수치들을 입력할 렉트
				FloatRect icon[3];	// 회복, 포만, 골드 아이콘을 배치할 렉트
				for (int k = 0; k < 3; k++)
				{
					icon[k] = FloatRect(relativeRc.right - 40, relativeRc.top + 100 + (k * 30), relativeRc.right - 10, relativeRc.top + 130 + (k * 30));
					//D2D_RENDERER->drawRectangle(icon[k], D2D1::ColorF::Magenta, 1, 1);
					value[k] = FloatRect(icon[k].left - 80, icon[k].top, icon[k].left, icon[k].bottom);
					//D2D_RENDERER->drawRectangle(value[k], D2D1::ColorF::Magenta, 1, 1);
				}

				//일시적으로 변화되는 스탯(체력 회복, 포만률, 소지금액(가격))
				int oneceStatCurrHp = foodOneceStat.currHp;
				float oneceStatCurrSatiety = foodOneceStat.currSatiety;
				int price = _foods[i]->getPrice();
				if (oneceStatCurrHp > 0)
				{
					D2D_RENDERER->renderTextField(value[0].left, value[0].top, to_wstring(oneceStatCurrHp), D2D1::ColorF::White, 25,
						value[0].getWidth(), value[0].getHeight(), 1, DWRITE_TEXT_ALIGNMENT_TRAILING, L"Aa카시오페아");
				}
				D2D_RENDERER->renderTextField(value[1].left, value[1].top, to_wstring(static_cast<int>(oneceStatCurrSatiety)), D2D1::ColorF::White, 25,
					value[1].getWidth(), value[1].getHeight(), 1, DWRITE_TEXT_ALIGNMENT_TRAILING, L"Aa카시오페아");
				D2D_RENDERER->renderTextField(value[2].left, value[2].top, to_wstring(price), D2D1::ColorF::White, 25,
					value[2].getWidth(), value[2].getHeight(), 1, DWRITE_TEXT_ALIGNMENT_TRAILING, L"Aa카시오페아");
				//아이콘 렌더
				_healIcon->setScale(2);
				_satietyIcon->setScale(2);
				_goldIcon->setScale(3);
				if (oneceStatCurrHp > 0) _healIcon->render(icon[0].getCenter());
				_satietyIcon->render(icon[1].getCenter());
				_goldIcon->render(icon[2].getCenter());
			}
		}
		else //판매완료
		{
			_foodListItemSoldOut->render(relativeRc.getCenter(), relativeRc.getSize());
		}
	}

	//음식 리스트 창
	//D2D_RENDERER->drawRectangle(_foodListViewRc, D2D1::ColorF::White, 1, 1);
	_foodListView->render(_foodListViewRc.getCenter(), _foodListViewRc.getSize());
	//뒷배경2
	D2D_RENDERER->fillRectangle(FloatRect(0, 0, WINSIZEX, 180), 34, 32, 52, 1);
	D2D_RENDERER->fillRectangle(_bgRc2, 34, 32, 52, 1);
	
	//상단 라벨
	_baseLabel->render(Vector2(WINSIZEX / 2, 80), Vector2(WINSIZEX, 160));
	//창닫기 버튼
	if (_exitRc.ptInRect(_ptMouse))
	{
		_exitBtnSelected->render(_exitRc.getCenter(), _exitRc.getSize());
	}
	else
	{
		_exitBtn->render(_exitRc.getCenter(), _exitRc.getSize());
	}
	
	//스크롤
	//_scrollBarBg->render(_scrollBarBgRc.getCenter(), _scrollBarBgRc.getSize());
	_scrollBarBg->render(_scrollBar.bgRc.getCenter(), _scrollBar.bgRc.getSize());
	_scrollBarHeader->render(_scrollBar.scrollRc.getCenter(), _scrollBar.scrollRc.getSize());

	//포만감 게이지 창
	_satietyBaseBack->render(_satietyRc.getCenter(), _satietyRc.getSize());
	//포만률 색 채우기
	_currSatietyRateFillRc = FloatRect(140.0, 800.0, 140 + (static_cast<float>(_player->getSatiety()) / _player->getCurrStat().maxSatiety) * _satietyRateRc.getSize().x, 880.0);
	D2D_RENDERER->fillRectangle(_currSatietyRateFillRc, 247, 183, 61, 1);
	//포만률 게이지 프레임 및 아이콘 텍스트 표시
	_satietyBase->render(_satietyRc.getCenter(), _satietyRc.getSize());
	_satietyIcon->render(Vector2(_satietyRc.left + 71, _satietyRc.getCenter().y+2), Vector2(_satietyIcon->getSize().x * 4, _satietyIcon->getSize().y * 3.7));
	//D2D_RENDERER->drawRectangle(_satietyRateRc, D2D1::ColorF::Magenta, 1, 1);
	D2D_RENDERER->renderTextField(_satietyRateRc.left, _satietyRateRc.top, to_wstring(_player->getSatiety()) + L" / " + to_wstring(_player->getCurrStat().maxSatiety), 
		RGB(255, 255, 255), 30, _satietyRateRc.getWidth(), _satietyRateRc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aa카시오페아", 0);
	//D2D_RENDERER->renderTextField(_satietyRc.left + 130, _satietyRc.getCenter().y + 2, to_wstring(/*스탯->현재 포만률 / 최대 포만률*/)) ....
	
	//현재 체력 게이지 창
	_lifeBaseBack->render(_lifeGaugeRc.getCenter(), _lifeGaugeRc.getSize());
	float hpRatio = (static_cast<float>(_player->getCurrHp()) / _player->getMaxHp());	 // 체력비율 (현재 체력 / 전체 체력)
	float width = (_lifeGaugeRc.getSize().x) * hpRatio;	// 현재 남은 체력게이지의 x축 길이 계산
	if (FLOAT_EQUAL(hpRatio, 1) || FLOAT_EQUAL(hpRatio, 0))
	{
		FloatRect currHpGauge = FloatRect(_lifeGaugeRc.left+5, _lifeGaugeRc.top, _lifeGaugeRc.left + width, _lifeGaugeRc.bottom);
		_currLifeGauge->render(currHpGauge.getCenter(), currHpGauge.getSize());
		D2D_RENDERER->drawRectangle(currHpGauge, D2D1::ColorF::Magenta, 1, 1);
	}
	else
	{ 
		FloatRect currHpGauge = FloatRect(_lifeGaugeRc.left+5, _lifeGaugeRc.top, max(_lifeGaugeRc.left + 1, _lifeGaugeRc.left + width - 14), _lifeGaugeRc.bottom);
		_currLifeGauge->render(currHpGauge.getCenter(), currHpGauge.getSize());
		FloatRect currHpWave = FloatRect(currHpGauge.right - 1, currHpGauge.top, currHpGauge.right + 14, currHpGauge.bottom);
		_currLifeGaugeWave->aniRender(currHpWave.getCenter(), currHpWave.getSize(), _currHpAni);
		//D2D_RENDERER->drawRectangle(currHpGauge, D2D1::ColorF::White, 1, 1);
		//D2D_RENDERER->drawRectangle(currHpWave, D2D1::ColorF::Magenta, 1, 1);
	}
	_lifeBase->render(_lifeGaugeRc.getCenter(), _lifeGaugeRc.getSize());
	D2D_RENDERER->renderTextField(_lifeGaugeRc.left, _lifeGaugeRc.top, to_wstring(_player->getCurrHp()) + L" / " + to_wstring(_player->getMaxHp()), D2D1::ColorF::White, 40,
		_lifeGaugeRc.getWidth(), _lifeGaugeRc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aa카시오페아", 0);
	//금액 창
	_goldBaseBack->render(_goldBaseRc.getCenter(), _goldBaseRc.getSize());
	_goldBase->render(_goldBaseRc.getCenter(), _goldBaseRc.getSize());
	//D2D_RENDERER->drawRectangle(_goldAmountRc, D2D1::ColorF::White, 1, 1);	//금액 텍스트 적을 칸
	D2D_RENDERER->renderTextField(_goldAmountRc.left, _goldAmountRc.top, to_wstring(_player->getGold()), D2D1::ColorF::White, 25,
		_goldAmountRc.getWidth(), _goldAmountRc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_TRAILING, L"Aa카시오페아", 0);
	//D2D_RENDERER->drawRectangle(_goldIconRc, D2D1::ColorF::White, 1, 1);	//아이콘 그릴 칸
	_goldIcon->render(_goldIconRc.getCenter(), Vector2(_goldIcon->getSize().x * 4, _goldIcon->getSize().y * 4));
}

