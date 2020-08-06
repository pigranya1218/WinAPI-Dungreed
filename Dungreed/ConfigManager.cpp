#include "stdafx.h"
#include "ConfigManager.h"

void ConfigManager::init()
{
	_header = IMAGE_MANAGER->findImage("OPTION_HEADER");
	_background = IMAGE_MANAGER->findImage("OPTION_BG");
	_exitButton = IMAGE_MANAGER->findImage("BUTTON_EXIT");
	_exitRc = FloatRect(WINSIZEX - 150, 30, WINSIZEX - 20, 140);

	_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].name = L"음악 볼륨";
	_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].ratio = 0.7;
	_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].textRc = FloatRect(270, 290, 670, 335);
	_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].progressRc = FloatRect(730, 300, 1200, 325);
	_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].handleRc = FloatRect(round(_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].progressRc.left + _progressVolume[static_cast<int> (SOUND_TYPE::BGM)].progressRc.getSize().x * _progressVolume[static_cast<int> (SOUND_TYPE::BGM)].ratio - 20), 
		_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].progressRc.top - 5,
		round(_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].progressRc.left + _progressVolume[static_cast<int> (SOUND_TYPE::BGM)].progressRc.getSize().x * _progressVolume[static_cast<int> (SOUND_TYPE::BGM)].ratio + 20), 
		_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].progressRc.bottom + 5);
	_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].name = L"효과음 볼륨";
	_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].ratio = 0.7;
	_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].textRc = FloatRect(270, 345, 670, 390);
	_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].progressRc = FloatRect(730, 355, 1200, 380);
	_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].handleRc = FloatRect(round(_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].progressRc.left + _progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].progressRc.getSize().x * _progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].ratio - 20),
		_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].progressRc.top - 5,
		round(_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].progressRc.left + _progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].progressRc.getSize().x * _progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].ratio + 20),
		_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].progressRc.bottom + 5);

	_soundBar = IMAGE_MANAGER->findImage("SOUND_BAR");
	_soundHandle = IMAGE_MANAGER->findImage("SOUND_HANDLE");
	_dragIndex = -1;
}

void ConfigManager::update()
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

	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		// 음량 조절
		for(int i = 0 ; i < 2 ; i++)
		{ 
			if (_progressVolume[i].handleRc.ptInRect(_ptMouse))
			{
				_dragIndex = i;
			}
			else if (_progressVolume[i].progressRc.ptInRect(_ptMouse))
			{
				_progressVolume[i].ratio = (_ptMouse.x - _progressVolume[i].progressRc.left) / _progressVolume[i].progressRc.getSize().x;
				_progressVolume[i].handleRc = FloatRect(round(_progressVolume[i].progressRc.left + _progressVolume[i].progressRc.getSize().x * _progressVolume[i].ratio - 20), 
					_progressVolume[i].progressRc.top - 5,
					round(_progressVolume[i].progressRc.left + _progressVolume[i].progressRc.getSize().x * _progressVolume[i].ratio + 20), 
					_progressVolume[i].progressRc.bottom + 5);
			}
		}
	}

	if (_dragIndex >= 0)
	{
		_progressVolume[_dragIndex].ratio = (_ptMouse.x - _progressVolume[_dragIndex].progressRc.left) / _progressVolume[_dragIndex].progressRc.getSize().x;
		_progressVolume[_dragIndex].ratio = min(_progressVolume[_dragIndex].ratio, 1);
		_progressVolume[_dragIndex].ratio = max(_progressVolume[_dragIndex].ratio, 0);
		_progressVolume[_dragIndex].handleRc = FloatRect(round(_progressVolume[_dragIndex].progressRc.left + _progressVolume[_dragIndex].progressRc.getSize().x * _progressVolume[_dragIndex].ratio - 20),
			_progressVolume[_dragIndex].progressRc.top - 5,
			round(_progressVolume[_dragIndex].progressRc.left + _progressVolume[_dragIndex].progressRc.getSize().x * _progressVolume[_dragIndex].ratio + 20),
			_progressVolume[_dragIndex].progressRc.bottom + 5);
	}

	if (KEY_MANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_dragIndex = -1;
	}
}

void ConfigManager::render()
{
	// BASE
	_background->render(Vector2(WINSIZEX / 2, WINSIZEY / 2), Vector2(WINSIZEX + 100, WINSIZEY + 100));
	_header->render(Vector2(WINSIZEX / 2, WINSIZEX * _header->getRatio() * 0.5 + 10), Vector2(WINSIZEX, static_cast<int>(WINSIZEX * _header->getRatio())));
	_exitButton->render(_exitRc.getCenter(), _exitRc.getSize());

	// VOLUME
	D2D_RENDERER->renderTextField(0, 210, L"사운드", RGB(189, 189, 189), 50, WINSIZEX, 50, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);
	for (int i = 0; i < 2; i++)
	{
		D2D_RENDERER->renderTextField(_progressVolume[i].textRc.left, _progressVolume[i].textRc.top, _progressVolume[i].name, 45, 
			_progressVolume[i].textRc.getSize().x, 45, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_TRAILING);
		_soundBar->render(_progressVolume[i].progressRc.getCenter(), _progressVolume[i].progressRc.getSize());
		_soundHandle->setScale(4);
		_soundHandle->render(Vector2(_progressVolume[i].handleRc.getCenter()));
	}

	// GAME PLAY
	D2D_RENDERER->renderTextField(0, 420, L"게임 플레이", RGB(189, 189, 189), 50, WINSIZEX, 50, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);


	// CONTROL
	D2D_RENDERER->renderTextField(0, 620, L"컨트롤", RGB(189, 189, 189), 50, WINSIZEX, 50, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);


	IMAGE_MANAGER->findImage("CURSOR_BASIC")->setScale(5);
	IMAGE_MANAGER->findImage("CURSOR_BASIC")->render(Vector2(_ptMouse.x, _ptMouse.y));
}
