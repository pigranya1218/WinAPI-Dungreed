#include "Player.h"
#include "StatUI.h"


void StatUI::init()
{
	_isActive = false;

	//바탕 이미지
	_statBaseImg = IMAGE_MANAGER->findImage("UI/STAT/BASE");
	_foodBaseImg = IMAGE_MANAGER->findImage("UI/STAT/BASE");
	_statBaseRc = FloatRect(20, 150, 560, 540);
	_foodBaseRc = FloatRect(20, 555, 510, WINSIZEY - 70);

	//창닫기 이미지
	_exitImg = IMAGE_MANAGER->findImage("BUTTON_EXIT");
	_exitSelectImg = IMAGE_MANAGER->findImage("BUTTON_EXIT_SELECTED");
	_exitRc = FloatRect(440, 60, 560, 140);

	//스탯 요소 이미지
	for (int i = 0; i < 12; i++)
	{
		//스탯 이미지 할당
		STAT_TYPE type = static_cast<STAT_TYPE>(i);
		string key = _playerStat->getStatString(type, true);
		_statEntity[i].icon = IMAGE_MANAGER->findImage(key);
		_statEntity[i].iconSelected = IMAGE_MANAGER->findImage(key + "_SELECTED");
	}

	//스탯 아이콘 배치
	//50 * 50 size
	_statEntity[0].iconRc = FloatRect(40, 210, 90, 260);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i * 3 + j + 1 > 11) continue;
			_statEntity[i * 3 + j + 1].iconRc = FloatRect(40 + 170 * j, 270 + 65 * i, 90 + 170 * j, 320 + 65 * i);
		}
	}
}

void StatUI::release()
{
}

void StatUI::update(float elapsedTime)
{
	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_exitRc.ptInRect(_ptMouse))
		{
			_isActive = false;
		}
	}
}

void StatUI::render()
{
	//바탕
	_statBaseImg->render(_statBaseRc.getCenter(), _statBaseRc.getSize());
	_foodBaseImg->render(_foodBaseRc.getCenter(), _foodBaseRc.getSize());
	string statname = PlayerStat::getStatString(STAT_TYPE::ATTACK_SPEED, false);
	
	// 창닫기
	if (_exitRc.ptInRect(_ptMouse))
	{
		_exitSelectImg->render(_exitRc.getCenter(), _exitRc.getSize());
	}
	else
	{
		_exitImg->render(_exitRc.getCenter(), _exitRc.getSize());
	}
	
	// STATUS, FOOD 제목
	D2D_RENDERER->renderTextField(_statBaseRc.left, _statBaseRc.top - 5, L"STATUS", RGB(255, 255, 255), 
		42, _statBaseRc.getWidth(), 70, 1.f, DWRITE_TEXT_ALIGNMENT_CENTER, L"Alagard", 0);
	D2D_RENDERER->renderTextField(_foodBaseRc.left, _foodBaseRc.top - 5, L"FOODS", RGB(255, 255, 255),
		42, _foodBaseRc.getWidth(), 70, 1.f, DWRITE_TEXT_ALIGNMENT_CENTER, L"Alagard", 0);
	
	// 스탯
	PlayerStat stat = _player->getCurrStat();
	for (int i = 0; i < 12; i++)
	{
		if (_statEntity[i].iconRc.ptInRect(_ptMouse))
		{
			_statEntity[i].iconSelected->render(_statEntity[i].iconRc.getCenter(), _statEntity[i].iconRc.getSize());
		}
		else
		{
			_statEntity[i].icon->render(_statEntity[i].iconRc.getCenter(), _statEntity[i].iconRc.getSize());
		}
		D2D_RENDERER->renderTextField(_statEntity[i].iconRc.right + 20, _statEntity[i].iconRc.top, to_wstring(static_cast<int>(stat.getStat(static_cast<STAT_TYPE>(i)))), RGB(255, 255, 255), 35, 100, 50, 1.f);
	}
}

