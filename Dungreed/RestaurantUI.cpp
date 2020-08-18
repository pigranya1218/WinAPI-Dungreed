#include "stdafx.h"
#include "RestaurantUI.h"

void RestaurantUI::init()
{
	_isActive = false;

	//â�ݱ� ��ư
	_exitRc = FloatRect(WINSIZEX - 150, 40, WINSIZEX - 30, 130);
}

void RestaurantUI::release()
{
}

void RestaurantUI::update(float elapsedTime)
{
	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//â�ݱ�
		if (_exitRc.ptInRect(_ptMouse))
		{
			_isActive = false;
		}
	}
}

void RestaurantUI::render()
{
	//��� ��
	_baseLabel->render(Vector2(WINSIZEX / 2, 80), Vector2(WINSIZEX, 160));

	//â�ݱ� ��ư
	if (_exitRc.ptInRect(_ptMouse))
	{
		_exitBtnSelected->render(_exitRc.getCenter(), _exitRc.getSize());
	}
	else
	{
		_exitBtn->render(_exitRc.getCenter(), _exitRc.getSize());
	}
}
