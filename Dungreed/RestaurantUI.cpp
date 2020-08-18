#include "stdafx.h"
#include "RestaurantUI.h"

void RestaurantUI::init()
{
	_isActive = false;
	//��ü �޹��
	//_bgRc = FloatRect(Vector2(WINSIZEX / 2, WINSIZEY / 2), Vector2(WINSIZEX, WINSIZEY));
	_bgRc = FloatRect(0, 0, WINSIZEX, WINSIZEY);
	//â�ݱ� ��ư
	_exitRc = FloatRect(WINSIZEX - 150, 40, WINSIZEX - 30, 130);
	//����Ʈ ���
	_foodListViewRc = FloatRect(30, 200, 530, 800);
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
	//��ü �޹��
	D2D_RENDERER->fillRectangle(_bgRc, 34, 32, 52, 1, 0, Vector2(0, 0));
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

	//����Ʈ �޹��
	_foodListView->render(_foodListViewRc.getCenter(), _foodListViewRc.getSize());
}
