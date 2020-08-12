#include "stdafx.h"
#include "DataManager.h"

void DataManager::init()
{
	_isActive = false;
	_exitButton = IMAGE_MANAGER->findImage("BUTTON_EXIT");
	_exitRc = FloatRect(WINSIZEX - 150, 30, WINSIZEX - 20, 130);

	// TODO : 데이터 읽음

	for (int i = 0; i < 3; i++)
	{
		_loadInfos[i].playTime = 60 * i + 42 * (i + 1);
		_loadInfos[i].level = i * 10 + 1;
		_loadInfos[i].highStage = i * 2 + 1;
		_loadInfos[i].gold = i * 1000 + 300;
		_loadRc[i] = FloatRect(90 + (480 * i), 150, 540 + (480 * i), 830);
		_deleteRc[i] = FloatRect(_loadRc[i].left + 85, 715.0, _loadRc[i].right - 85, 795.0);
	}

	_slotImg = IMAGE_MANAGER->findImage("SLOT");
	_selectedSlot = -1;
	_selectedDelete = -1;
}

void DataManager::update()
{
	if (_exitRc.ptInRect(_ptMouse))
	{
		_exitButton = IMAGE_MANAGER->findImage("BUTTON_EXIT_SELECTED");
		if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_isActive = false;
			return;
		}
	}
	else
	{
		_exitButton = IMAGE_MANAGER->findImage("BUTTON_EXIT");
	}

	_selectedSlot = -1;
	_selectedDelete = -1;

	for (int i = 0; i < 3; i++)
	{
		if (_loadRc[i].ptInRect(_ptMouse))
		{
			_selectedSlot = i;
		}
		if (_deleteRc[i].ptInRect(_ptMouse))
		{
			_selectedDelete = i;
		}
	}
	
	if (KEY_MANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		_isActive = false;
	}
}

void DataManager::render()
{
	D2D_RENDERER->fillRectangle(FloatRect(0, 0, WINSIZEX, WINSIZEY), 0, 0, 0, 0.8);

	_exitButton->render(_exitRc.getCenter(), _exitRc.getSize());

	for (int i = 0; i < 3; i++)
	{
		if (_selectedSlot == i)
		{
			IMAGE_MANAGER->findImage("SLOT_SELECTED")->render(_loadRc[i].getCenter(), _loadRc[i].getSize());
		}
		else
		{
			IMAGE_MANAGER->findImage("SLOT")->render(_loadRc[i].getCenter(), _loadRc[i].getSize());
		}

		if (_selectedDelete == i)
		{
			IMAGE_MANAGER->findImage("SLOT_DELETE_SELECTED")->render(_deleteRc[i].getCenter(), _deleteRc[i].getSize());
		}
		else
		{
			IMAGE_MANAGER->findImage("SLOT_DELETE")->render(_deleteRc[i].getCenter(), _deleteRc[i].getSize());
		}
		D2D_RENDERER->renderTextField(_deleteRc[i].left, _deleteRc[i].top, L"Delete", RGB(112, 112, 125), 35, _deleteRc[i].getSize().x, _deleteRc[i].getSize().y, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);

		char buffer[50];
		sprintf_s(buffer, "SLOT_NUM_%d", (i + 1));
		IMAGE_MANAGER->findImage(buffer)->setScale(5);
		IMAGE_MANAGER->findImage(buffer)->render(Vector2(_loadRc[i].getCenter().x, 230.0));

		wstring data;
		D2D_RENDERER->renderTextField(_loadRc[i].left, 340, L"<플레이 시간>", RGB(195, 195, 195), 25, _loadRc[i].getSize().x, 25, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);
		data = ((_loadInfos[i].playTime / 60 < 10)?L"0":L"") + to_wstring(_loadInfos[i].playTime / 60) + L"H " 
			+ ((_loadInfos[i].playTime % 60 < 10) ? L"0" : L"") + to_wstring(_loadInfos[i].playTime % 60) + L"M";
		D2D_RENDERER->renderTextField(_loadRc[i].left, 375, data, RGB(195, 195, 195), 25, _loadRc[i].getSize().x, 25, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);

		D2D_RENDERER->renderTextField(_loadRc[i].left, 455, L"<도달한 층>", RGB(195, 195, 195), 25, _loadRc[i].getSize().x, 25, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);
		data = to_wstring(_loadInfos[i].highStage) + L"F";
		D2D_RENDERER->renderTextField(_loadRc[i].left, 490, data, RGB(195, 195, 195), 25, _loadRc[i].getSize().x, 25, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);

		D2D_RENDERER->renderTextField(_loadRc[i].left, 580, L"<소지금>", RGB(195, 195, 195), 25, _loadRc[i].getSize().x, 25, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);
		data = to_wstring(_loadInfos[i].gold) + L"G";
		D2D_RENDERER->renderTextField(_loadRc[i].left, 615, data, RGB(195, 195, 195), 25, _loadRc[i].getSize().x, 25, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);

	}

	IMAGE_MANAGER->findImage("CURSOR_BASIC")->setScale(5);
	IMAGE_MANAGER->findImage("CURSOR_BASIC")->render(Vector2(_ptMouse.x, _ptMouse.y));
}
