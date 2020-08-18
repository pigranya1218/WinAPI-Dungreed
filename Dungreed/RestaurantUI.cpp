#include "stdafx.h"
#include "RestaurantUI.h"

void RestaurantUI::init()
{
	_isActive = false;

	//창닫기 버튼
	_exitRc = FloatRect(WINSIZEX - 150, 40, WINSIZEX - 30, 130);
}

void RestaurantUI::release()
{
}

void RestaurantUI::update(float elapsedTime)
{
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
}
