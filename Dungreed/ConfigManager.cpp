#include "stdafx.h"
#include "ConfigManager.h"

void ConfigManager::init()
{
	_header = IMAGE_MANAGER->findImage("OPTION_HEADER");
	_background = IMAGE_MANAGER->findImage("OPTION_BG");
	_exitRc = FloatRect(WINSIZEX - 150, 30, WINSIZEX - 20, 140);

	_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].name = L"음악 볼륨";
	_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].ratio = 0.7;
	_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].textRc = FloatRect(270, 290, 370, 335);
	_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].name = L"효과음 볼륨";
	_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].ratio = 0.7;
	_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].textRc = FloatRect(270, 345, 370, 390);
}

void ConfigManager::update()
{
	if (!_isActive) return;


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

void ConfigManager::render()
{
	if (!_isActive) return;


	// BASE
	_background->render(Vector2(WINSIZEX / 2, WINSIZEY / 2), Vector2(WINSIZEX + 100, WINSIZEY + 100));
	_header->render(Vector2(WINSIZEX / 2, WINSIZEX * _header->getRatio() * 0.5 + 10), Vector2(WINSIZEX, static_cast<int>(WINSIZEX * _header->getRatio())));
	_exitButton->render(_exitRc.getCenter(), _exitRc.getSize());

	// VOLUME
	D2D_RENDERER->renderTextField(0, 210, L"사운드", RGB(189, 189, 189), 50, WINSIZEX, 50, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);
	for (int i = 0; i < 2; i++)
	{
		D2D_RENDERER->renderTextField(_progressVolume[i].textRc.left, _progressVolume[i].textRc.top, _progressVolume[i].name, 45, 
			_progressVolume[i].textRc.right, 45, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_TRAILING);
	}

	// GAME PLAY
	D2D_RENDERER->renderTextField(0, 420, L"게임 플레이", RGB(189, 189, 189), 50, WINSIZEX, 50, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);


	// CONTROL
	D2D_RENDERER->renderTextField(0, 620, L"컨트롤", RGB(189, 189, 189), 50, WINSIZEX, 50, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);


	IMAGE_MANAGER->findImage("CURSOR_BASIC")->setScale(5);
	IMAGE_MANAGER->findImage("CURSOR_BASIC")->render(Vector2(_ptMouse.x, _ptMouse.y));
}
