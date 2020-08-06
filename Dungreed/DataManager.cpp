#include "stdafx.h"
#include "DataManager.h"

void DataManager::init()
{
	_isActive = false;
	_exitButton = IMAGE_MANAGER->findImage("BUTTON_EXIT");
	_exitRc = FloatRect(WINSIZEX - 135, 15, WINSIZEX - 5, 125);

	// TODO : 데이터 읽음


	for (int i = 0; i < 3; i++)
	{
		_loadInfos[i].level = i * 10 + 1;
		_loadInfos[i].highStage = i * 2 + 1;
		_loadInfos[i].gold = i * 1000 + 300;
		_loadRc[i] = FloatRect();
	}
}

void DataManager::update()
{
	if (_exitRc.ptInRect(_ptMouse))
	{
		_exitButton = IMAGE_MANAGER->findImage("BUTTON_EXIT_SELECTED");
		if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_isActive = false;
		}
	}
	else
	{
		_exitButton = IMAGE_MANAGER->findImage("BUTTON_EXIT");
	}


	
}

void DataManager::render()
{
	D2D_RENDERER->fillRectangle(FloatRect(0, 0, WINSIZEX, WINSIZEY), 0, 0, 0, 0.8);

	_exitButton->render(_exitRc.getCenter(), _exitRc.getSize());


	IMAGE_MANAGER->findImage("CURSOR_BASIC")->setScale(5);
	IMAGE_MANAGER->findImage("CURSOR_BASIC")->render(Vector2(_ptMouse.x, _ptMouse.y));
}
