#include "stdafx.h"
#include "RestaurantUI.h"
#include "Player.h"

void RestaurantUI::init()
{
	_isActive = false;
	//전체 뒷배경
	//_bgRc = FloatRect(Vector2(WINSIZEX / 2, WINSIZEY / 2), Vector2(WINSIZEX, WINSIZEY));
	_bgRc = FloatRect(0, 0, WINSIZEX, WINSIZEY);
	//창닫기 버튼
	_exitRc = FloatRect(WINSIZEX - 150, 40, WINSIZEX - 30, 130);
	//음식 목록 창
	_foodListViewRc = FloatRect(20, 180, 500, 780);
	//포만감 게이지
	_satietyRc = FloatRect(15, 800, 515, 880);
	//음식 이미지 창(테이블)
	_foodTableViewRc = FloatRect(550, 180, WINSIZEX - 20, 780);
	//스크롤
	_scrollBarBgRc = FloatRect(510, 180, 540, 780);
	//금액 창
	_goldBaseRc = FloatRect(1400, 800, WINSIZEX - 20, 880);
	//금액 텍스트 렌더용 렉트
	_goldAmountRc = FloatRect(1410, 800, WINSIZEX - 80, 880);
	//골드 아이콘 렉트
	_goldIconRc = FloatRect(WINSIZEX - 80, 800, WINSIZEX - 20, 880);

	//테이블 이미지 애니메이션
	_tableAni = new Animation;
	_tableAni->init(_foodTableFrameView->getWidth(), _foodTableFrameView->getHeight(), _foodTableFrameView->getMaxFrameX(), _foodTableFrameView->getMaxFrameY());
	_tableAni->setPlayFrame(0, _foodTableFrameView->getMaxFrameX(), false, true);
	_tableAni->setFPS(10);
	_tableAni->start();
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
	D2D_RENDERER->fillRectangle(_bgRc, 34, 32, 52, 1, 0, Vector2(0, 0));
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
	//음식 리스트 창
	//D2D_RENDERER->drawRectangle(_foodListViewRc, D2D1::ColorF::White, 1, 1);
	_foodListView->render(_foodListViewRc.getCenter(), _foodListViewRc.getSize());
	//스크롤
	_scrollBarBg->render(_scrollBarBgRc.getCenter(), _scrollBarBgRc.getSize());
	//포만감 게이지 창
	_satietyBaseBack->render(_satietyRc.getCenter(), _satietyRc.getSize());
	_satietyBase->render(_satietyRc.getCenter(), _satietyRc.getSize());
	_satietyIcon->render(Vector2(_satietyRc.left + 71, _satietyRc.getCenter().y+2), Vector2(_satietyIcon->getSize().x * 4, _satietyIcon->getSize().y * 3.7));
	//D2D_RENDERER->renderTextField(_satietyRc.left + 130, _satietyRc.getCenter().y + 2, to_wstring(/*스탯->현재 포만률 / 최대 포만률*/)) ....
	//우측 음식 이미지 창
	_foodTableFrameView->aniRender(_foodTableViewRc.getCenter(), _foodTableViewRc.getSize(), _tableAni);
	_foodTableViewBase->render(_foodTableViewRc.getCenter(), _foodTableViewRc.getSize());
	//금액 창
	_goldBaseBack->render(_goldBaseRc.getCenter(), _goldBaseRc.getSize());
	_goldBase->render(_goldBaseRc.getCenter(), _goldBaseRc.getSize());
	D2D_RENDERER->drawRectangle(_goldAmountRc, D2D1::ColorF::White, 1, 1);	//금액 텍스트 적을 칸
	D2D_RENDERER->drawRectangle(_goldIconRc, D2D1::ColorF::White, 1, 1);	//아이콘 그릴 칸
	_goldIcon->render(_goldIconRc.getCenter(), Vector2(_goldIcon->getSize().x * 4, _goldIcon->getSize().y * 4));
}
