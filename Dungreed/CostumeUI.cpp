#include "stdafx.h"
#include "CostumeUI.h"
#include "Player.h"
#include "Costume.h"

void CostumeUI::init()
{
	_isActive = false;
	_cosType = COSTUME_TYPE::ALICE;

	//창닫기 버튼
	_exitRc = FloatRect(WINSIZEX - 150, 40, WINSIZEX - 30, 130);

	//중단 코스튬 선택 스크롤을 입힐 렉트
	_midRc = FloatRect(0, 160, WINSIZEX, WINSIZEY - 200);

	//costume cell
	//셀의 가로 크기 : 360, 세로 크기는 162 ~ WINSIZEY - 202
	_costumeCell[0].cellRect = FloatRect(0, 162, 360, WINSIZEY - 202);
	for (int i = 0; i < 7; i++)
	{
		//셀 렉트 위치 조정
		if (i > 0)
		{
			_costumeCell[i].cellRect = FloatRect(360 * i, 162, 360 * i + 360, WINSIZEY - 202);
		}
		if (i < 5)
		{
			//샘플 이미지 할당
			_costumeCell[i].costumeSample = IMAGE_MANAGER->findImage("UI/COSTUME/" + to_string(i));
		}
	}

	//_costumeCell[0].text = L""
}

void CostumeUI::release()
{
}

void CostumeUI::update(float elapsedTime)
{
	
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
	}
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
	
	//코스튬 셀 (카메라 렌더 필요)
	for (int i = 0; i < 7; i++)
	{
		//셀 뒷배경
		_costumeCell[i].costumeBackImg->render(_costumeCell[i].cellRect.getCenter(), _costumeCell[i].cellRect.getSize(), false);
		//락/언락 배경
		if (i != static_cast<int>(_cosType))
		{
			//_costumeCell[i].costumeUnlockedImg->setScale(5.2);
			_costumeCell[i].costumeUnlockedImg->setSize(Vector2(300, 500));
			_costumeCell[i].costumeUnlockedImg->render(Vector2(_costumeCell[i].cellRect.getCenter().getIntX(), _costumeCell[i].cellRect.getCenter().getIntY() + 10), false);
		}
		//현재 장착중인 코스튬
		else 
		{
			_costumeCell[i].costumeEquippedImg->setSize(Vector2(300, 500));
			_costumeCell[i].costumeEquippedImg->render(Vector2(_costumeCell[i].cellRect.getCenter().getIntX(), _costumeCell[i].cellRect.getCenter().getIntY() + 10), false);
			//_costumeCell[i].costumeEquippedImg->render(_costumeCell[i].cellRect.getCenter(), false);
		}
		//현재 선택한 코스튬
		if (_costumeCell[i].cellRect.ptInRect(_ptMouse))
		{
			_costumeCell[i].costumeSelectedImg->setSize(Vector2(300, 500));
			_costumeCell[i].costumeSelectedImg->render(Vector2(_costumeCell[i].cellRect.getCenter().getIntX(), _costumeCell[i].cellRect.getCenter().getIntY() + 10), false);
			//설명
			D2D_RENDERER->renderTextField(20, WINSIZEY - 200, _costumeCell[i].text, D2D1::ColorF::White, 20,
				WINSIZEX, WINSIZEY, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.f);
		}

		//코스튬 샘플 이미지
		if (i > 4) continue;
		_costumeCell[i].costumeSample->setScale(5);
		_costumeCell[i].costumeSample->render(Vector2(_costumeCell[i].cellRect.getCenter().getIntX(), _costumeCell[i].cellRect.getCenter().getIntY() + 131), false); 
		
		//_costumeCell[i].costumeSample->render(_costumeCell[i].cellRect.getCenter(), false);
		/*D2D_RENDERER->drawRectangle(_costumeCell[i].cellRect, D2D1::ColorF::Enum::Red, 1.0f, 3.0f);
		D2D_RENDERER->drawRectangle(FloatRect(_costumeCell[i].cellRect.getCenter(), _costumeCell[i].costumeSample->getSize(), PIVOT::CENTER), D2D1::ColorF::Enum::Red, 1.0f, 3.0f);*/
	}
	
	_costumeBaseDownImg->render(Vector2(WINSIZEX / 2, WINSIZEY - 100), Vector2(WINSIZEX, 200));
}
