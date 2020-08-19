#include "stdafx.h"
#include "RestaurantUI.h"
#include "EggFriedFood.h"
#include "Player.h"
#include "PlayerStat.h"

void RestaurantUI::init()
{

	for (int i = 0; i < 5; i++)
	{
		_foods.push_back(new EggFriedFood);
	}

	_isActive = false;
	//전체 뒷배경
	//_bgRc = FloatRect(Vector2(WINSIZEX / 2, WINSIZEY / 2), Vector2(WINSIZEX, WINSIZEY));
	_bgRc = FloatRect(0, 0, WINSIZEX, WINSIZEY);
	_bgRc2 = FloatRect(0, 780, 500, WINSIZEY);
	//창닫기 버튼
	_exitRc = FloatRect(WINSIZEX - 150, 40, WINSIZEX - 30, 130);
	//음식 목록 창
	_foodListViewRc = FloatRect(20, 180, 500, 780);
	//포만감 게이지
	_satietyRc = FloatRect(15, 800, 515, 880);
	//포만률 값을 표시할 렉트
	_satietyRateRc = FloatRect(140, 800, 515, 880);
	//음식 이미지 창(테이블)
	_foodTableViewRc = FloatRect(550, 180, WINSIZEX - 20, 780);
	//체력 게이지 창
	_lifeGaugeRc = FloatRect(570, 200, 870, 300);
	//스크롤
	_scrollBarBgRc = FloatRect(510, 180, 540, 780);
	//금액 창
	_goldBaseRc = FloatRect(1400, 800, WINSIZEX - 20, 880);
	//금액 텍스트 렌더용 렉트
	_goldAmountRc = FloatRect(1410, 800, WINSIZEX - 80, 880);
	//골드 아이콘 렉트
	_goldIconRc = FloatRect(WINSIZEX - 80, 800, WINSIZEX - 20, 880);

	//음식 리스트 항목 창
	for (int i = 0; i < 5; i++)
	{
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

	//_foodImg = _foods[0]->getImage();
}

void RestaurantUI::release()
{
	_tableAni->release();
	delete _tableAni;
}

void RestaurantUI::update(float elapsedTime)
{
	_tableAni->frameUpdate(elapsedTime);
	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//창닫기
		if (_exitRc.ptInRect(_ptMouse))
		{
			_isActive = false;
		}
	}
}

void RestaurantUI::render()
{
	//전체 뒷배경
	D2D_RENDERER->fillRectangle(_bgRc, 34, 32, 52, 1);
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
	//음식 리스트의 항목
	for (int i = 0; i < 5; i++)
	{
		if (_foodItems[i].baseRc.ptInRect(_ptMouse))
		{
			_foodItems[i]._foodListItemSelected->render(_foodItems[i].baseRc.getCenter(), _foodItems[i].baseRc.getSize());
			//_foodImg = _foods[i]->getImage();
			//_foodImg->render(_foodTableViewRc.getCenter());
		}
		else
		{
			_foodItems[i]._foodListItem->render(_foodItems[i].baseRc.getCenter(), _foodItems[i].baseRc.getSize());
		}
		//아이템에 따른 변화되는 스탯 받아오는 작업
		PlayerStat foodStat = _foods[i]->getAddStat();
		//food 벡터에 있는 아이템들을 리스트 foodItems에 표시
		D2D_RENDERER->renderTextField(_foodItems[i].baseRc.left + 10, _foodItems[i].baseRc.top, TTYONE_UTIL::stringTOwsting(_foods[i]->getName()),
			RGB(255, 178, 144), 40, _foodItems[i].baseRc.getWidth(), _foodItems[i].baseRc.getHeight() - 150, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Alagard", 0);
		int count = 0;
		for (int j = 0; j < static_cast<int>(STAT_TYPE::END); j++)
		{
			STAT_TYPE statType = static_cast<STAT_TYPE>(j);
			int statValue = foodStat.getStat(statType);
			string statString = foodStat.getStatString(statType, false);
			if (statValue != 0)
			{
				count++;
				D2D_RENDERER->renderTextField(_foodItems[i].baseRc.left + 15, _foodItems[i].baseRc.top + 40 * count, L"▶",
					RGB(255, 255, 255), 30, _foodItems[i].baseRc.getWidth(), _foodItems[i].baseRc.getHeight() - 150, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Alagard", 0);
				D2D_RENDERER->renderTextField(_foodItems[i].baseRc.left + 50, _foodItems[i].baseRc.top + 40 * count, ((statValue >= 0) ? (L"+"):(L"")) + to_wstring(statValue), (statValue >= 0) ? RGB(0, 255, 0) : RGB(255, 0, 0)
					, 30, _foodItems[i].baseRc.getWidth(), _foodItems[i].baseRc.getHeight() - 150, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Alagard", 0);
				D2D_RENDERER->renderTextField(_foodItems[i].baseRc.left + 100, _foodItems[i].baseRc.top + 40 * count, TTYONE_UTIL::stringTOwsting(statString), RGB(255, 255, 255)
					, 30, _foodItems[i].baseRc.getWidth(), _foodItems[i].baseRc.getHeight() - 150, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Alagard", 0);
			}
		}

	}
	//음식 리스트 창
	//D2D_RENDERER->drawRectangle(_foodListViewRc, D2D1::ColorF::White, 1, 1);
	_foodListView->render(_foodListViewRc.getCenter(), _foodListViewRc.getSize());
	//뒷배경2
	D2D_RENDERER->fillRectangle(_bgRc2, 34, 32, 52, 1);
	//스크롤
	_scrollBarBg->render(_scrollBarBgRc.getCenter(), _scrollBarBgRc.getSize());
	//포만감 게이지 창
	_satietyBaseBack->render(_satietyRc.getCenter(), _satietyRc.getSize());
	_satietyBase->render(_satietyRc.getCenter(), _satietyRc.getSize());
	_satietyIcon->render(Vector2(_satietyRc.left + 71, _satietyRc.getCenter().y+2), Vector2(_satietyIcon->getSize().x * 4, _satietyIcon->getSize().y * 3.7));
	//D2D_RENDERER->drawRectangle(_satietyRateRc, D2D1::ColorF::Magenta, 1, 1);
	D2D_RENDERER->renderTextField(_satietyRateRc.left, _satietyRateRc.top, to_wstring(_player->getCurrStat().currSatiety) + L" / " + to_wstring(_player->getCurrStat().maxSatiety), 
		RGB(255, 255, 255), 30, _satietyRateRc.getWidth(), _satietyRateRc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Alagard", 0);
	//D2D_RENDERER->renderTextField(_satietyRc.left + 130, _satietyRc.getCenter().y + 2, to_wstring(/*스탯->현재 포만률 / 최대 포만률*/)) ....
	//우측 음식 이미지 창
	_foodTableFrameView->aniRender(_foodTableViewRc.getCenter(), _foodTableViewRc.getSize(), _tableAni);
	_foodTableViewBase->render(_foodTableViewRc.getCenter(), _foodTableViewRc.getSize());
	//현재 체력 게이지 창
	_lifeBaseBack->render(_lifeGaugeRc.getCenter(), _lifeGaugeRc.getSize());
	_lifeBase->render(_lifeGaugeRc.getCenter(), _lifeGaugeRc.getSize());
	D2D_RENDERER->renderTextField(_lifeGaugeRc.left, _lifeGaugeRc.top, to_wstring(_player->getCurrHp()) + L" / " + to_wstring(_player->getMaxHp()), D2D1::ColorF::White, 40,
		_lifeGaugeRc.getWidth(), _lifeGaugeRc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Alagard", 0);
	//금액 창
	_goldBaseBack->render(_goldBaseRc.getCenter(), _goldBaseRc.getSize());
	_goldBase->render(_goldBaseRc.getCenter(), _goldBaseRc.getSize());
	//D2D_RENDERER->drawRectangle(_goldAmountRc, D2D1::ColorF::White, 1, 1);	//금액 텍스트 적을 칸
	D2D_RENDERER->renderTextField(_goldAmountRc.left, _goldAmountRc.top, to_wstring(_player->getGold()), D2D1::ColorF::White, 25,
		_goldAmountRc.getWidth(), _goldAmountRc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_TRAILING, L"Alagard", 0);
	//D2D_RENDERER->drawRectangle(_goldIconRc, D2D1::ColorF::White, 1, 1);	//아이콘 그릴 칸
	_goldIcon->render(_goldIconRc.getCenter(), Vector2(_goldIcon->getSize().x * 4, _goldIcon->getSize().y * 4));
}
