#include "stdafx.h"
#include "ConfigManager.h"

wstring ConfigManager::getActionName(ACTION_TYPE type)
{
	wstring result;
	switch (type)
	{
	case ACTION_TYPE::MOVE_LEFT:
	{
		result = L"왼쪽 이동";
	}
	break;
	case ACTION_TYPE::MOVE_RIGHT:
	{
		result = L"오른쪽 이동";
	}
	break;
	case ACTION_TYPE::MOVE_UP:
	{
		result = L"위쪽 이동";
	}
	break;
	case ACTION_TYPE::MOVE_DOWN:
	{
		result = L"아래쪽 이동";
	}
	break;
	case ACTION_TYPE::ATTACK:
	{
		result = L"발사";
	}
	break;
	case ACTION_TYPE::MAIN_SKILL:
	{
		result = L"주스킬";
	}
	break;
	case ACTION_TYPE::SUB_SKILL:
	{
		result = L"보조스킬";
	}
	break;
	case ACTION_TYPE::CHANGE_WEAPON:
	{
		result = L"무기 교체";
	}
	break;
	case ACTION_TYPE::DASH:
	{
		result = L"대쉬";
	}
	break;
	case ACTION_TYPE::RELOAD:
	{
		result = L"재장전";
	}
	break;
	case ACTION_TYPE::JUMP:
	{
		result = L"점프";
	}
	break;
	case ACTION_TYPE::INVENTORY:
	{
		result = L"인벤토리";
	}
	break;
	case ACTION_TYPE::MAP:
	{
		result = L"지도";
	}
	break;
	case ACTION_TYPE::STAT:
	{
		result = L"캐릭터 능력치";
	}
	break;
	case ACTION_TYPE::INTERACTION:
	{
		result = L"상호작용";
	}
	break;
	}

	return result;
}

Image * ConfigManager::getKeyImage(int key)
{
	switch (key)
	{
	case VK_LEFT:
		return IMAGE_MANAGER->findImage("KEY_LEFT");
	case VK_RIGHT:
		return IMAGE_MANAGER->findImage("KEY_RIGHT");
	case VK_UP:
		return IMAGE_MANAGER->findImage("KEY_UP");
	case VK_DOWN:
		return IMAGE_MANAGER->findImage("KEY_DOWN");

	case VK_LBUTTON:
		return IMAGE_MANAGER->findImage("KEY_LBUTTON");
	case VK_RBUTTON:
		return IMAGE_MANAGER->findImage("KEY_RBUTTON");
	
	case VK_LCONTROL:
		return IMAGE_MANAGER->findImage("KEY_CTRL");
	case VK_LSHIFT:
		return IMAGE_MANAGER->findImage("KEY_SHIFT");
	case VK_SPACE:
		return IMAGE_MANAGER->findImage("KEY_SPACE");
	case VK_TAB:
		return IMAGE_MANAGER->findImage("KEY_TAB");
	}

	if ((48 <= key && key <= 57) || (65 <= key && key <= 90))
	{
		char buffer[20];
		sprintf_s(buffer, "%c", key);
		string imageKey = "KEY_" + string(buffer);
		return IMAGE_MANAGER->findImage(imageKey);
	}

	return nullptr;
}

void ConfigManager::init()
{
	_header = IMAGE_MANAGER->findImage("OPTION_HEADER");
	_background = IMAGE_MANAGER->findImage("OPTION_BG");
	_exitButton = IMAGE_MANAGER->findImage("BUTTON_EXIT");
	_exitRc = FloatRect(WINSIZEX - 155, 35, WINSIZEX - 25, 135);

	// TODO: 설정값들 파일로부터 읽기

	_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].name = L"음악 볼륨";
	_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].ratio = 0.7;
	_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].textRc = FloatRect(270, 90, 670, 135);
	_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].progressRc = FloatRect(730, 100, 1200, 125);
	_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].handleRc = FloatRect(round(_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].progressRc.left + _progressVolume[static_cast<int> (SOUND_TYPE::BGM)].progressRc.getSize().x * _progressVolume[static_cast<int> (SOUND_TYPE::BGM)].ratio - 20), 
		_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].progressRc.top - 5,
		round(_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].progressRc.left + _progressVolume[static_cast<int> (SOUND_TYPE::BGM)].progressRc.getSize().x * _progressVolume[static_cast<int> (SOUND_TYPE::BGM)].ratio + 20), 
		_progressVolume[static_cast<int> (SOUND_TYPE::BGM)].progressRc.bottom + 5);
	_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].name = L"효과음 볼륨";
	_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].ratio = 0.7;
	_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].textRc = FloatRect(270, 145, 670, 190);
	_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].progressRc = FloatRect(730, 155, 1200, 180);
	_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].handleRc = FloatRect(round(_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].progressRc.left + _progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].progressRc.getSize().x * _progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].ratio - 20),
		_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].progressRc.top - 5,
		round(_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].progressRc.left + _progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].progressRc.getSize().x * _progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].ratio + 20),
		_progressVolume[static_cast<int> (SOUND_TYPE::EFFECT)].progressRc.bottom + 5);

	_soundBar = IMAGE_MANAGER->findImage("SOUND_BAR");
	_soundHandle = IMAGE_MANAGER->findImage("SOUND_HANDLE");
	_dragSoundIndex = -1;

	_cameraShake.name = L"화면 흔들림";
	_cameraShake.isCheck = true;
	_cameraShake.textRc = FloatRect(270, 295, 670, 340);
	_cameraShake.boxRc = FloatRect(950, 300, 990, 340);
	_cameraShake.alpha = 1;

	_isScroll = false;
	_scrollBar.totalHeight = 1560;
	_scrollBar.height = 700;
	_scrollBar.ratio = 0;
	_scrollBar.bgRc = FloatRect(1550, 180, 1590, 895);
	_scrollBar.scrollRc = FloatRect(1550.0, 180.0, 1590.0, 180 + ((static_cast<float>(_scrollBar.height) / _scrollBar.totalHeight) * (_scrollBar.bgRc.bottom - _scrollBar.bgRc.top)));
	_camera.setConfig(0, 180, WINSIZEX, _scrollBar.height, 0, 0, 0, _scrollBar.totalHeight - _scrollBar.height);

	_keyChangeRemain = 0;

	// KEYMAP, 나중에 함수로 뺄 것
	for (int i = 0; i < static_cast<int>(ACTION_TYPE::END); i++)
	{
		_keyMapButton[i].actionName = getActionName(static_cast<ACTION_TYPE>(i));
		_keyMapButton[i].nameRc = FloatRect(WINSIZEX / 2 - 300, 520 + (i * 70), WINSIZEX / 2 - 100, 580 + (i * 70));
		_keyMapButton[i].buttonRc = FloatRect(WINSIZEX / 2 + 100, 520 + (i * 70), WINSIZEX / 2 + 300, 580 + (i * 70));
	}
	// KEYMAP init
	_keyMap.insert(make_pair(ACTION_TYPE::MOVE_LEFT, 'A'));
	_keyMap.insert(make_pair(ACTION_TYPE::MOVE_RIGHT, 'D'));
	_keyMap.insert(make_pair(ACTION_TYPE::MOVE_UP, 'W'));
	_keyMap.insert(make_pair(ACTION_TYPE::MOVE_DOWN, 'S'));
	_keyMap.insert(make_pair(ACTION_TYPE::ATTACK, VK_LBUTTON));
	_keyMap.insert(make_pair(ACTION_TYPE::RELOAD, 'R'));
	_keyMap.insert(make_pair(ACTION_TYPE::DASH, VK_RBUTTON));
	_keyMap.insert(make_pair(ACTION_TYPE::JUMP, VK_SPACE));
	_keyMap.insert(make_pair(ACTION_TYPE::MAIN_SKILL, 'Q'));
	_keyMap.insert(make_pair(ACTION_TYPE::SUB_SKILL, 'E'));
	_keyMap.insert(make_pair(ACTION_TYPE::INVENTORY, 'V'));
	_keyMap.insert(make_pair(ACTION_TYPE::MAP, VK_TAB));
	_keyMap.insert(make_pair(ACTION_TYPE::STAT, 'C'));
	_keyMap.insert(make_pair(ACTION_TYPE::INTERACTION, 'F'));
	_keyMap.insert(make_pair(ACTION_TYPE::CHANGE_WEAPON, VK_LSHIFT));

	_lastPtMouse = _ptMouse;
}

void ConfigManager::update()
{
	if (_keyChangeRemain > 0)
	{
		int newKey = KEY_MANAGER->getWhichKeyDown();
		if (newKey != -1)
		{
			_keyMap.find(static_cast<ACTION_TYPE>(_keyButtonIndex))->second = newKey;
			_keyChangeRemain = 0;
		}
		else
		{
			_keyChangeRemain -= TIME_MANAGER->getElapsedTime();
			return;
		}
	}


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

	_keyButtonIndex = -1;
	for (int i = 0; i < static_cast<int>(ACTION_TYPE::END); i++)
	{
		if (_keyMapButton[i].buttonRc.ptInRect(_camera.getAbsolutePt(_ptMouse)))
		{
			_keyButtonIndex = i;
			break;
		}
	}

	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		// 음량 조절
		for(int i = 0 ; i < 2 ; i++)
		{ 
			if (_progressVolume[i].handleRc.ptInRect(_camera.getAbsolutePt(_ptMouse)))
			{
				_dragSoundIndex = i;
			}
			else if (_progressVolume[i].progressRc.ptInRect(_camera.getAbsolutePt(_ptMouse)))
			{
				_progressVolume[i].ratio = (_ptMouse.x - _progressVolume[i].progressRc.left) / _progressVolume[i].progressRc.getSize().x;
				_progressVolume[i].handleRc = FloatRect(round(_progressVolume[i].progressRc.left + _progressVolume[i].progressRc.getSize().x * _progressVolume[i].ratio - 20), 
					_progressVolume[i].progressRc.top - 5,
					round(_progressVolume[i].progressRc.left + _progressVolume[i].progressRc.getSize().x * _progressVolume[i].ratio + 20), 
					_progressVolume[i].progressRc.bottom + 5);
			}
		}

		// 화면 흔들림 조정
		if (_cameraShake.boxRc.ptInRect(_camera.getAbsolutePt(_ptMouse)))
		{
			_cameraShake.isCheck = !_cameraShake.isCheck;
		}

		// 키 조정
		for (int i = 0; i < static_cast<int>(ACTION_TYPE::END); i++)
		{
			if (_keyMapButton[i].buttonRc.ptInRect(_camera.getAbsolutePt(_ptMouse)))
			{
				_keyChangeRemain = 3;
				break;
			}
		}

		// 드래그 조정
		if (_scrollBar.scrollRc.ptInRect(_ptMouse))
		{
			_isScroll = true;
		}
	}

	if (_dragSoundIndex >= 0)
	{
		_progressVolume[_dragSoundIndex].ratio = (_ptMouse.x - _progressVolume[_dragSoundIndex].progressRc.left) / _progressVolume[_dragSoundIndex].progressRc.getSize().x;
		_progressVolume[_dragSoundIndex].ratio = min(_progressVolume[_dragSoundIndex].ratio, 1);
		_progressVolume[_dragSoundIndex].ratio = max(_progressVolume[_dragSoundIndex].ratio, 0);
		_progressVolume[_dragSoundIndex].handleRc = FloatRect(round(_progressVolume[_dragSoundIndex].progressRc.left + _progressVolume[_dragSoundIndex].progressRc.getSize().x * _progressVolume[_dragSoundIndex].ratio - 20),
			_progressVolume[_dragSoundIndex].progressRc.top - 5,
			round(_progressVolume[_dragSoundIndex].progressRc.left + _progressVolume[_dragSoundIndex].progressRc.getSize().x * _progressVolume[_dragSoundIndex].ratio + 20),
			_progressVolume[_dragSoundIndex].progressRc.bottom + 5);
	}

	if (_isScroll)
	{
		Vector2 currCenter = _scrollBar.scrollRc.getCenter();
		int move = _ptMouse.y - _lastPtMouse.y;
		currCenter.y += move;
		currCenter.y = min(currCenter.y, _scrollBar.bgRc.bottom - (_scrollBar.scrollRc.getSize().y / 2));
		currCenter.y = max(currCenter.y, _scrollBar.bgRc.top + (_scrollBar.scrollRc.getSize().y / 2));
		_scrollBar.scrollRc = FloatRect(currCenter, _scrollBar.scrollRc.getSize(), PIVOT::CENTER);
		_scrollBar.ratio = (currCenter.y - (_scrollBar.bgRc.top + (_scrollBar.scrollRc.getSize().y / 2))) 
			/ ((_scrollBar.bgRc.bottom - (_scrollBar.scrollRc.getSize().y / 2)) - (_scrollBar.bgRc.top + (_scrollBar.scrollRc.getSize().y / 2)));
		_camera.setT((_scrollBar.totalHeight - _scrollBar.height) * _scrollBar.ratio);
	}

	if (KEY_MANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_dragSoundIndex = -1;
		_isScroll = false;
	}

	if (KEY_MANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		_isActive = false;
	}

	if (_cameraShake.isCheck)
	{
		_cameraShake.alpha = min(1.0, _cameraShake.alpha + TIME_MANAGER->getElapsedTime() * 6);
	}
	else
	{
		_cameraShake.alpha = max(0.0, _cameraShake.alpha - TIME_MANAGER->getElapsedTime() * 6);
	}

	_lastPtMouse = _ptMouse;

}

void ConfigManager::render()
{
	// BASE
	_background->render(Vector2(WINSIZEX / 2, WINSIZEY / 2), Vector2(WINSIZEX + 100, WINSIZEY + 100));

	// VOLUME
	D2D_RENDERER->renderTextField(0, static_cast<int>(_camera.getRelativeY(20.0f)), L"사운드", RGB(189, 189, 189), 50, WINSIZEX, 50, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);
	for (int i = 0; i < 2; i++)
	{
		D2D_RENDERER->renderTextField(_progressVolume[i].textRc.left, _camera.getRelativeY(_progressVolume[i].textRc.top), _progressVolume[i].name, RGB(255, 255, 255), 45, 
			_progressVolume[i].textRc.getSize().x, 45, DWRITE_TEXT_ALIGNMENT_TRAILING);
		_soundBar->render(_camera.getRelativeV2(_progressVolume[i].progressRc.getCenter()), _progressVolume[i].progressRc.getSize());
		_soundHandle->setScale(4);
		_soundHandle->render(_camera.getRelativeV2(Vector2(_progressVolume[i].handleRc.getCenter())));
	}


	// GAME PLAY
	D2D_RENDERER->renderTextField(0, static_cast<int>(_camera.getRelativeY(215.0f)), L"게임 플레이", RGB(189, 189, 189), 50, WINSIZEX, 50, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);
	D2D_RENDERER->renderTextField(_cameraShake.textRc.left, _camera.getRelativeY(_cameraShake.textRc.top), _cameraShake.name, RGB(255, 255, 255), 45,
		_cameraShake.textRc.getSize().x, 45, DWRITE_TEXT_ALIGNMENT_TRAILING);
	D2D_RENDERER->drawRectangle(_camera.getRelativeFR(_cameraShake.boxRc), D2D1::ColorF::Enum::White, 1, 5);
	{
		Vector2 size = _cameraShake.boxRc.getSize();
		size.x -= 15;
		size.y -= 15;
		D2D_RENDERER->fillRectangle(_camera.getRelativeFR(FloatRect(_cameraShake.boxRc.getCenter(), size, PIVOT::CENTER)), D2D1::ColorF::Enum::Red, _cameraShake.alpha);
	}

	
	// CONTROL
	D2D_RENDERER->renderTextField(0, _camera.getRelativeY(380.0f), L"컨트롤", RGB(189, 189, 189), 50, WINSIZEX, 50, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);
	D2D_RENDERER->renderTextField(WINSIZEX * 0.25, _camera.getRelativeY(450.0f), L"액션", RGB(189, 189, 189), 40, WINSIZEX * 0.25, 50, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);
	D2D_RENDERER->renderTextField(WINSIZEX * 0.5, _camera.getRelativeY(450.0f), L"입력", RGB(189, 189, 189), 40, WINSIZEX * 0.25, 50, 1.0, DWRITE_TEXT_ALIGNMENT_CENTER);

	for (int i = 0; i < static_cast<int>(ACTION_TYPE::END); i++)
	{
		IMAGE_MANAGER->findImage("KEYMAP_HEADER")->render(_camera.getRelativeV2(_keyMapButton[i].nameRc.getCenter()), _keyMapButton[i].nameRc.getSize());
		D2D_RENDERER->renderTextField(_camera.getRelativeX(_keyMapButton[i].nameRc.left), _camera.getRelativeY(_keyMapButton[i].nameRc.top), _keyMapButton[i].actionName, RGB(255, 255, 255),
			30, _keyMapButton[i].nameRc.getSize().x, _keyMapButton[i].nameRc.getSize().y, 1, DWRITE_TEXT_ALIGNMENT_CENTER);
		
		if (_keyButtonIndex == i)
		{
			IMAGE_MANAGER->findImage("KEYMAP_BUTTON_SELECTED")->render(_camera.getRelativeV2(_keyMapButton[i].buttonRc.getCenter()), _keyMapButton[i].buttonRc.getSize());
		}
		else
		{
			IMAGE_MANAGER->findImage("KEYMAP_BUTTON")->render(_camera.getRelativeV2(_keyMapButton[i].buttonRc.getCenter()), _keyMapButton[i].buttonRc.getSize());
		}
		getKeyImage(_keyMap.find(static_cast<ACTION_TYPE>(i))->second)->setScale(4);
		getKeyImage(_keyMap.find(static_cast<ACTION_TYPE>(i))->second)->render(_camera.getRelativeV2(_keyMapButton[i].buttonRc.getCenter()));
	}

	if (_keyChangeRemain)
	{
		D2D_RENDERER->fillRectangle(FloatRect(0, 0, WINSIZEX, WINSIZEY), 0, 0, 0, 0.7);
		D2D_RENDERER->renderTextField(0, 300, L"Type the key you want.", RGB(255, 255, 255), 50, WINSIZEX, 50, 1, DWRITE_TEXT_ALIGNMENT_CENTER);
	}

	// HEADER
	D2D_RENDERER->fillRectangle(FloatRect(0, 0, WINSIZEX, 180), 34, 32, 52, 1);
	_header->render(Vector2(WINSIZEX / 2, WINSIZEX * _header->getRatio() * 0.5 + 10), Vector2(WINSIZEX, static_cast<int>(WINSIZEX * _header->getRatio())));
	_exitButton->render(_exitRc.getCenter(), _exitRc.getSize());
	
	// SCROLL BAR
	IMAGE_MANAGER->findImage("SCROLL_BG")->render(_scrollBar.bgRc.getCenter(), _scrollBar.bgRc.getSize());
	IMAGE_MANAGER->findImage("SCROLL_HEADER")->render(_scrollBar.scrollRc.getCenter(), _scrollBar.scrollRc.getSize());

	IMAGE_MANAGER->findImage("CURSOR_BASIC")->setScale(5);
	IMAGE_MANAGER->findImage("CURSOR_BASIC")->render(Vector2(_ptMouse.x, _ptMouse.y));
}
