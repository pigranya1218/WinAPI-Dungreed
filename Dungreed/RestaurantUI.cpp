#include "stdafx.h"
#include "RestaurantUI.h"
#include "Player.h"

void RestaurantUI::init()
{
	_isActive = false;
	//��ü �޹��
	//_bgRc = FloatRect(Vector2(WINSIZEX / 2, WINSIZEY / 2), Vector2(WINSIZEX, WINSIZEY));
	_bgRc = FloatRect(0, 0, WINSIZEX, WINSIZEY);
	//â�ݱ� ��ư
	_exitRc = FloatRect(WINSIZEX - 150, 40, WINSIZEX - 30, 130);
	//���� ��� â
	_foodListViewRc = FloatRect(20, 180, 500, 780);
	//������ ������
	_satietyRc = FloatRect(15, 800, 515, 880);
	//���� �̹��� â(���̺�)
	_foodTableViewRc = FloatRect(550, 180, WINSIZEX - 20, 780);
	//��ũ��
	_scrollBarBgRc = FloatRect(510, 180, 540, 780);
	//�ݾ� â
	_goldBaseRc = FloatRect(1400, 800, WINSIZEX - 20, 880);
	//�ݾ� �ؽ�Ʈ ������ ��Ʈ
	_goldAmountRc = FloatRect(1410, 800, WINSIZEX - 80, 880);
	//��� ������ ��Ʈ
	_goldIconRc = FloatRect(WINSIZEX - 80, 800, WINSIZEX - 20, 880);

	//���̺� �̹��� �ִϸ��̼�
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
	//���� ����Ʈ â
	//D2D_RENDERER->drawRectangle(_foodListViewRc, D2D1::ColorF::White, 1, 1);
	_foodListView->render(_foodListViewRc.getCenter(), _foodListViewRc.getSize());
	//��ũ��
	_scrollBarBg->render(_scrollBarBgRc.getCenter(), _scrollBarBgRc.getSize());
	//������ ������ â
	_satietyBaseBack->render(_satietyRc.getCenter(), _satietyRc.getSize());
	_satietyBase->render(_satietyRc.getCenter(), _satietyRc.getSize());
	_satietyIcon->render(Vector2(_satietyRc.left + 71, _satietyRc.getCenter().y+2), Vector2(_satietyIcon->getSize().x * 4, _satietyIcon->getSize().y * 3.7));
	//D2D_RENDERER->renderTextField(_satietyRc.left + 130, _satietyRc.getCenter().y + 2, to_wstring(/*����->���� ������ / �ִ� ������*/)) ....
	//���� ���� �̹��� â
	_foodTableFrameView->aniRender(_foodTableViewRc.getCenter(), _foodTableViewRc.getSize(), _tableAni);
	_foodTableViewBase->render(_foodTableViewRc.getCenter(), _foodTableViewRc.getSize());
	//�ݾ� â
	_goldBaseBack->render(_goldBaseRc.getCenter(), _goldBaseRc.getSize());
	_goldBase->render(_goldBaseRc.getCenter(), _goldBaseRc.getSize());
	D2D_RENDERER->drawRectangle(_goldAmountRc, D2D1::ColorF::White, 1, 1);	//�ݾ� �ؽ�Ʈ ���� ĭ
	D2D_RENDERER->drawRectangle(_goldIconRc, D2D1::ColorF::White, 1, 1);	//������ �׸� ĭ
	_goldIcon->render(_goldIconRc.getCenter(), Vector2(_goldIcon->getSize().x * 4, _goldIcon->getSize().y * 4));
}
