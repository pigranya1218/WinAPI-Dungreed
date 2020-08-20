#include "stdafx.h"
#include "CostumeUI.h"
#include "Player.h"
#include "PlayerStat.h"
#include "Costume.h"
#include "MetalPlateCos.h"
#include "AliceCos.h"
#include "RedLotusCos.h"
#include "PickaxCos.h"

void CostumeUI::init()
{
	_isActive = false;
	_mouseMove = false;
	_isScroll = false;

	_lastPtMouse = _ptMouse;

	_cosType = COSTUME_TYPE::ALICE;

	//창닫기 버튼
	_exitRc = FloatRect(WINSIZEX - 150, 40, WINSIZEX - 30, 130);

	//중단 코스튬 선택 스크롤을 입힐 렉트
	_midRc = FloatRect(0, 160, WINSIZEX, WINSIZEY - 200);

	//costume cell
	//셀의 가로 크기 : 360, 세로 크기는 162 ~ WINSIZEY - 202
	_costumeCell[0].cellRect = FloatRect(0, 162, 360, WINSIZEY - 202);
	for (int i = 0; i < static_cast<int>(COSTUME_TYPE::END); i++)
	{
		COSTUME_TYPE type = static_cast<COSTUME_TYPE>(i);
		Costume* costume = DATA_MANAGER->getCostume(type);
		//셀 렉트 위치 조정
		if (i > 0)
		{
			_costumeCell[i].cellRect = FloatRect(360 * i, 162, 360 * i + 360, WINSIZEY - 202);
		}
		if (i < 5)
		{
			//샘플 이미지 할당
			_costumeCell[i].costumeSample = IMAGE_MANAGER->findImage("UI/COSTUME/" + costume->getCostumeName());
		}

		_costumeCell[i].cosTitle = costume->getTitle();
		_costumeCell[i].cosSummary = costume->getSummary();
		_costumeCell[i].cosDetails = costume->getDetails();
		_costumeCell[i].differStat = costume->getDifferStat();

	}

	//스크롤 바
	_isScroll = false;
	_scrollBar.totalWidth = 360 * static_cast<int>(COSTUME_TYPE::END);
	_scrollBar.width = WINSIZEX;
	_scrollBar.ratio = 0;
	_scrollBar.bgRc = FloatRect(0, WINSIZEY - 200, WINSIZEX, WINSIZEY - 190);
	_scrollBar.scrollRc = FloatRect(0.0, static_cast<float>(WINSIZEY - 200), (static_cast<float>(_scrollBar.width) / _scrollBar.totalWidth) * (_scrollBar.bgRc.right - _scrollBar.bgRc.left), static_cast<float>(WINSIZEY - 190));
}

void CostumeUI::release()
{
}

void CostumeUI::update(float elapsedTime)
{
	CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, _scrollBar.totalWidth - WINSIZEX, 0);
	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//창닫기
		if (_exitRc.ptInRect(_ptMouse))
		{
			_isActive = false;
		}
		//코스튬 선택
		for (int i = 0; i < 5; i++)
		{
			if (_costumeCell[i].cellRect.ptInRect(_ptMouse))
			{
				_cosType = COSTUME_TYPE(i);
				_player->setCurrCostume(DATA_MANAGER->getCostume(_cosType));
			}
		}
		//스크롤 드래그
		if (_scrollBar.scrollRc.ptInRect(_ptMouse))
		{
			_isScroll = true;
		}
	}

	/*if (KEY_MANAGER->isStayKeyDown(VK_LBUTTON))
	{
		CAMERA->setConfig(360 * static_cast<int>(COSTUME_TYPE::END), 0, _scrollBar.width, WINSIZEY - 364, 0, 0, _scrollBar.totalWidth - _scrollBar.width, 0);
	}*/
	if (_isScroll)
	{
		Vector2 currCenter = _scrollBar.scrollRc.getCenter();
		int move = _ptMouse.x - _lastPtMouse.x;
		currCenter.x += move;
		currCenter.x = min(currCenter.x, _scrollBar.bgRc.right - (_scrollBar.scrollRc.getSize().x / 2));
		currCenter.x = max(currCenter.x, _scrollBar.bgRc.left + (_scrollBar.scrollRc.getSize().x / 2));
		_scrollBar.scrollRc = FloatRect(currCenter, _scrollBar.scrollRc.getSize(), PIVOT::CENTER);
		_scrollBar.ratio = (currCenter.x - (_scrollBar.bgRc.left + (_scrollBar.scrollRc.getSize().x / 2)))
			/ ((_scrollBar.bgRc.right - (_scrollBar.scrollRc.getSize().x / 2)) - (_scrollBar.bgRc.left + (_scrollBar.scrollRc.getSize().x / 2)));
		CAMERA->setL((_scrollBar.totalWidth - _scrollBar.width) * _scrollBar.ratio);
	}

	if (KEY_MANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_isScroll = false;
	}

	_lastPtMouse = _ptMouse;
}

void CostumeUI::render()
{
	_costumeBaseUpImg->render(Vector2(WINSIZEX / 2, 80), Vector2(WINSIZEX, 160));
	//창닫기 버튼
	if (_exitRc.ptInRect(_ptMouse))
	{
		_exitBtnSelected->render(_exitRc.getCenter(), _exitRc.getSize(), false);
	}
	else
	{
		_exitBtn->render(_exitRc.getCenter(), _exitRc.getSize(), false);
	}
	
	D2D_RENDERER->drawRectangle(_midRc, D2D1::ColorF::White, 3, 3);
	_costumeBaseDownImg->render(Vector2(WINSIZEX / 2, WINSIZEY - 100), Vector2(WINSIZEX, 200));
	//코스튬 셀 (카메라 렌더 필요)
	for (int i = 0; i < static_cast<int>(COSTUME_TYPE::END); i++)
	{
		//셀 뒷배경
		//_costumeCell[i].costumeBackImg->render(_costumeCell[i].cellRect.getCenter(), _costumeCell[i].cellRect.getSize(), false);
		_costumeCell[i].costumeBackImg->render(Vector2(CAMERA->getRelativeX(_costumeCell[i].cellRect.getCenter().x ), _costumeCell[i].cellRect.getCenter().y), 
			_costumeCell[i].cellRect.getSize(), false);
		//락/언락 배경
		if (i != static_cast<int>(_cosType))
		{
			//_costumeCell[i].costumeUnlockedImg->setScale(5.2);
			_costumeCell[i].costumeUnlockedImg->setSize(Vector2(300, 500));
			//_costumeCell[i].costumeUnlockedImg->render(Vector2(_costumeCell[i].cellRect.getCenter().getIntX(), _costumeCell[i].cellRect.getCenter().getIntY() + 10), false);
			_costumeCell[i].costumeUnlockedImg->render(Vector2(CAMERA->getRelativeX(_costumeCell[i].cellRect.getCenter().x), _costumeCell[i].cellRect.getCenter().y + 10), false);
		}
		//현재 장착중인 코스튬
		else 
		{
			_costumeCell[i].costumeEquippedImg->setSize(Vector2(300, 500));
			//_costumeCell[i].costumeEquippedImg->render(Vector2(_costumeCell[i].cellRect.getCenter().getIntX(), _costumeCell[i].cellRect.getCenter().getIntY() + 10), false);
			_costumeCell[i].costumeEquippedImg->render(Vector2(CAMERA->getRelativeX(_costumeCell[i].cellRect.getCenter().x), _costumeCell[i].cellRect.getCenter().y + 10), false);
		}
		//현재 선택한 코스튬
		if (_costumeCell[i].cellRect.ptInRect(_ptMouse))
		{
			_costumeCell[i].costumeSelectedImg->setSize(Vector2(300, 500));
			//_costumeCell[i].costumeSelectedImg->render(Vector2(_costumeCell[i].cellRect.getCenter().getIntX(), _costumeCell[i].cellRect.getCenter().getIntY() + 10), false);
			_costumeCell[i].costumeSelectedImg->render(Vector2(CAMERA->getRelativeX(_costumeCell[i].cellRect.getCenter().x), _costumeCell[i].cellRect.getCenter().y + 10), false);

			//코스튬 이름
			D2D_RENDERER->renderTextField(20, WINSIZEY - 140, _costumeCell[i].cosTitle, RGB(255,246,18), 45,
				500, 0, 1.f, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aa카시오페아", 0.f);
			//코스튬 개요
			D2D_RENDERER->renderTextField(30, WINSIZEY - 80, _costumeCell[i].cosSummary, RGB(255, 255, 255), 25,
				500, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아", 0.f);
			//코스튬 상세내용
			if (_costumeCell[i].cosDetails != L"")
			{
				D2D_RENDERER->renderTextField(530, WINSIZEY - 140, L"▶", D2D1::ColorF::White, 25,
					WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아", 0.f);
				D2D_RENDERER->renderTextField(560, WINSIZEY - 140, _costumeCell[i].cosDetails, RGB(65,255,58), 25,
					WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아", 0.f);
			}
			//변동스탯
			wstring statValue1, statValue2, statValue3;
			wstring statName1, statName2, statName3;
			int stat1 = 0;
			int stat2 = 0;
			int stat3 = 0;
			//D2D1::ColorF::Enum color1, color2, color3;
			/*D2D1::ColorF::Enum color1 =  D2D1::ColorF::White;
			D2D1::ColorF::Enum color2 = D2D1::ColorF::White;
			D2D1::ColorF::Enum color3 = D2D1::ColorF::White;*/
			int r1, g1, b1;
			int r2, g2, b2;
			int r3, g3, b3;
		
			if (i > 0)
			{
				if (i == 1)
				{
					stat1 = static_cast<int>(_costumeCell[i].differStat->defense);
					//color1 = ((stat1 >= 0) ?  D2D1::ColorF::Green : D2D1::ColorF::Red);
					if (stat1 >= 0)
					{
						r1 = 65, g1 = 255, b1 = 58;
					}
					else if (stat1 < 0)
					{
						r1 = 255, g1 = 0, b1 = 0;
					}
					statValue1 = ((stat1 >= 0)? L"+" + to_wstring(stat1) : to_wstring(stat1));
					statName1 = TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::DEF, false));

					stat2 = _costumeCell[i].differStat->maxHp;
					//color2 = ((stat2 >= 0) ? D2D1::ColorF::Green : D2D1::ColorF::Red);
					if (stat2 >= 0)
					{
						r2 = 65, g2 = 255, b2 = 58;
					}
					else if (stat2 < 0)
					{
						r2 = 255, g2 = 0, b2 = 0;
					}
					statValue2 = ((stat2 >= 0) ? L"+" + to_wstring(stat2) : to_wstring(stat2));
					statName2 =	TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::MAX_HP, false));
				}
				if (i == 2)
				{
					stat1 = _costumeCell[i].differStat->maxHp;
					//color1 = ((stat1 >= 0) ? D2D1::ColorF::Green : D2D1::ColorF::Red);
					if (stat1 >= 0)
					{
						r1 = 65, g1 = 255, b1 = 58;
					}
					else if (stat1 < 0)
					{
						r1 = 255, g1 = 0, b1 = 0;
					}
					statValue1 = ((stat1 >= 0) ? L"+" + to_wstring(stat1) : to_wstring(stat1));
					statName1 = TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::MAX_HP, false));

					stat2 = static_cast<int>(_costumeCell[i].differStat->power);
					//color2 = ((stat2 >= 0) ? D2D1::ColorF::Green : D2D1::ColorF::Red);
					if (stat2 >= 0)
					{
						r2 = 65, g2 = 255, b2 = 58;
					}
					else if (stat2 < 0)
					{
						r2 = 255, g2 = 0, b2 = 0;
					}
					statValue2 = ((stat2 >= 0) ? L"+" + to_wstring(stat2) : to_wstring(stat2));
					statName2 = TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::POW, false));
				}
				if (i == 3)
				{
					stat1 = _costumeCell[i].differStat->maxHp;
					//color1 = ((stat1 >= 0) ? D2D1::ColorF::Green : D2D1::ColorF::Red);
					if (stat1 >= 0)
					{
						r1 = 65, g1 = 255, b1 = 58;
					}
					else if (stat1 < 0)
					{
						r1 = 255, g1 = 0, b1 = 0;
					}
					statValue1 = ((stat1 >= 0) ? L"+" + to_wstring(stat1) : to_wstring(stat1));
					statName1 = TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::MAX_HP, false));

					stat2 = static_cast<int>(_costumeCell[i].differStat->evasion);
					//color2 = ((stat2 >= 0) ? D2D1::ColorF::Green : D2D1::ColorF::Red);
					if (stat2 >= 0)
					{
						r2 = 65, g2 = 255, b2 = 58;
					}
					else if (stat2 < 0)
					{
						r2 = 255, g2 = 0, b2 = 0;
					}
					statValue2 = ((stat2 >= 0) ? L"+" + to_wstring(stat2) : to_wstring(stat2));
					statName2 = TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::EVADE, false));
				}
				if (i == 4)
				{
					stat1 = static_cast<int>(_costumeCell[i].differStat->dashDamage);
					//color1 = ((stat1 >= 0) ? D2D1::ColorF::Green : D2D1::ColorF::Red);
					if (stat1 >= 0)
					{
						r1 = 65, g1 = 255, b1 = 58;
					}
					else if (stat1 < 0)
					{
						r1 = 255, g1 = 0, b1 = 0;
					}
					statValue1 = ((stat1 >= 0) ? L"+" + to_wstring(stat1) : to_wstring(stat1)); 
					statName1 = TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::DASH_DAMAGE, false));

					stat2 = _costumeCell[i].differStat->maxDashCount;
					//color2 = ((stat2 >= 0) ? D2D1::ColorF::Green : D2D1::ColorF::Red);
					if (stat2 >= 0)
					{
						r2 = 65, g2 = 255, b2 = 58;
					}
					else if (stat2 < 0)
					{
						r2 = 255, g2 = 0, b2 = 0;
					}
					statValue2 = ((stat2 >= 0) ? L"+" + to_wstring(stat2) : to_wstring(stat2));
					statName2 = TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::MAX_DASH_COUNT, false));

					stat3 = static_cast<int>(_costumeCell[i].differStat->criticalChance);
					//color3 = ((stat3 >= 0) ? D2D1::ColorF::Green : D2D1::ColorF::Red);
					if (stat3 >= 0)
					{
						r3 = 65, g3 = 255, b3 = 58;
					}
					else if(stat3 < 0)
					{
						r3 = 255, g3 = 0, b3 = 0;
					}
					statValue3 = ((stat3 >= 0) ? L"+" + to_wstring(stat3) : to_wstring(stat3));
					statName3 = TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::CRITICAL, false));

					D2D_RENDERER->renderTextField(530, WINSIZEY - 50, L"▶", RGB(255,255,255), 25,
						WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아", 0.f);
					D2D_RENDERER->renderTextField(560, WINSIZEY - 50, statValue3, RGB(r3,g3,b3), 25,
						WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아", 0.f);
					D2D_RENDERER->renderTextField(605, WINSIZEY - 50, statName3, RGB(255, 255, 255), 25,
						WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아", 0.f);
				}
				D2D_RENDERER->renderTextField(530, WINSIZEY - 110, L"▶", RGB(255, 255, 255), 25,
					WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아", 0.f);
				D2D_RENDERER->renderTextField(560, WINSIZEY - 110, statValue1, RGB(r1, g1, b1), 25,
					WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아", 0.f);
				D2D_RENDERER->renderTextField(605, WINSIZEY - 110, statName1, RGB(255, 255, 255), 25,
					WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아", 0.f);

				D2D_RENDERER->renderTextField(530, WINSIZEY - 80, L"▶", RGB(255, 255, 255), 25,
					WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아", 0.f);
				D2D_RENDERER->renderTextField(560, WINSIZEY - 80, statValue2, RGB(r2, g2, b2), 25,
					WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아", 0.f);
				D2D_RENDERER->renderTextField(605, WINSIZEY - 80, statName2, RGB(255, 255, 255), 25,
					WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아", 0.f);
			}
		}
		//스크롤바
		//D2D_RENDERER->drawRectangle(_scrollBar.bgRc, D2D1::ColorF::Gray, 1, 1);
		D2D_RENDERER->fillRectangle(_scrollBar.bgRc, D2D1::ColorF::Gray, 1);
		//D2D_RENDERER->drawRectangle(_scrollBar.scrollRc, D2D1::ColorF::Cyan, 1, 1);
		D2D_RENDERER->fillRectangle(_scrollBar.scrollRc, D2D1::ColorF::Goldenrod, 1);

		//코스튬 샘플 이미지
		if (i >= static_cast<int>(COSTUME_TYPE::END)) continue;
		_costumeCell[i].costumeSample->setScale(5);
		//_costumeCell[i].costumeSample->render(Vector2(_costumeCell[i].cellRect.getCenter().getIntX(), _costumeCell[i].cellRect.getCenter().getIntY() + 131), false); 
		_costumeCell[i].costumeSample->render(Vector2(CAMERA->getRelativeX(_costumeCell[i].cellRect.getCenter().x), _costumeCell[i].cellRect.getCenter().y + 131), false);

		//_costumeCell[i].costumeSample->render(_costumeCell[i].cellRect.getCenter(), false);
		/*D2D_RENDERER->drawRectangle(_costumeCell[i].cellRect, D2D1::ColorF::Enum::Red, 1.0f, 3.0f);
		D2D_RENDERER->drawRectangle(FloatRect(_costumeCell[i].cellRect.getCenter(), _costumeCell[i].costumeSample->getSize(), PIVOT::CENTER), D2D1::ColorF::Enum::Red, 1.0f, 3.0f);*/
	}
	
	

}
