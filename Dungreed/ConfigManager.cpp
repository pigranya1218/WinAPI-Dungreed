#include "stdafx.h"
#include "ConfigManager.h"

void ConfigManager::init()
{
	_header = IMAGE_MANAGER->findImage("OPTION_HEADER");
	_background = IMAGE_MANAGER->findImage("OPTION_BG");
	_exitRc = FloatRect(WINSIZEX - 150, 30, WINSIZEX - 20, 140);
}

void ConfigManager::update()
{
	if (!_isActive) return;


	if (_exitRc.ptInRect(_ptMouse))
	{
		_exitButton = IMAGE_MANAGER->findImage("BUTTON_EXIT_SELECTED");
	}
	else
	{
		_exitButton = IMAGE_MANAGER->findImage("BUTTON_EXIT");
	}
}

void ConfigManager::render()
{
	if (!_isActive) return;

	_background->render(Vector2(WINSIZEX / 2, WINSIZEY / 2), Vector2(WINSIZEX + 100, WINSIZEY + 100));
	_header->render(Vector2(WINSIZEX / 2, WINSIZEX * _header->getRatio() * 0.5 + 10), Vector2(WINSIZEX, static_cast<int>(WINSIZEX * _header->getRatio())));
	_exitButton->render(_exitRc.getCenter(), _exitRc.getSize());

	IMAGE_MANAGER->findImage("CURSOR_BASIC")->setScale(5);
	IMAGE_MANAGER->findImage("CURSOR_BASIC")->render(Vector2(_ptMouse.x, _ptMouse.y));
}
