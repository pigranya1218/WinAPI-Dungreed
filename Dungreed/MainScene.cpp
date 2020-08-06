#include "stdafx.h"
#include "MainScene.h"

string MainScene::getImageName(string imageName, MENU menu) const
{
	string result = imageName + "_";
	if (_selected == menu)
	{
		result += "ON";
	}
	else
	{
		result += "OFF";
	}
	return result;
}

HRESULT MainScene::init()
{
	_birdImage = IMAGE_MANAGER->findImage("MAIN_SCENE/BIRD");
	_birdAni = new Animation;
	_birdAni->init(_birdImage->getWidth(), _birdImage->getHeight(), _birdImage->getMaxFrameX(), _birdImage->getMaxFrameY());
	_birdAni->setDefPlayFrame(false, true);
	_birdAni->setFPS(20);
	_birdAni->start();
	
	_frontCloud = IMAGE_MANAGER->findImage("MAIN_SCENE/FRONT_CLOUD");
	_frontSpeed = 2;
	_backCloud = IMAGE_MANAGER->findImage("MAIN_SCENE/BACK_CLOUD");
	_backSpeed = 1;

	_mouseMove = false;
	_lastMousePt = _ptMouse;

	_selected = MENU::PLAY;
	for (int i = 0; i < static_cast<UINT>(MENU::END); i++)
	{
		int posY = WINSIZEY / 2 + 160 + i * 70;
		_selectedRc[i] = FloatRect(Vector2(WINSIZEX / 2, posY), Vector2(400, 70), PIVOT::CENTER);
	}

	return S_OK;
}

void MainScene::release()
{
}

void MainScene::update()
{
	if (CONFIG_MANAGER->isActive()) 
	{ 
		CONFIG_MANAGER->update();
		return; 
	}

	_frontX += _frontSpeed;
	if (_frontX >= _frontCloud->getWidth() * 5)
	{
		_frontX -= _frontCloud->getWidth() * 5;
	}
	_backX += _backSpeed;
	if (_backX >= _backCloud->getWidth() * 5)
	{
		_backX -= _backCloud->getWidth() * 5;
	}

	_birdAni->frameUpdate(TIME_MANAGER->getElapsedTime());

	if (DATA_MANAGER->isActive())
	{
		DATA_MANAGER->update();
		return;
	}

	if ((_lastMousePt.x != _ptMouse.x || _lastMousePt.y != _ptMouse.y) || KEY_MANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_mouseMove = true;
		_lastMousePt = _ptMouse;
	}

	if (_mouseMove)
	{
		_mouseMove = false;
		for (int i = 0; i < static_cast<int>(MENU::END); i++)
		{
			if (_selectedRc[i].ptInRect(_ptMouse))
			{
				_selected = static_cast<MENU>(i);
				break;
			}
		}
	}


	if (KEY_MANAGER->isOnceKeyDown(VK_SPACE) || KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		switch (_selected)
		{
		case MENU::PLAY:
		{
			DATA_MANAGER->setActive(true);
		}
		break;
		case MENU::OPTION:
		{
			CONFIG_MANAGER->setActive(true);
		}
		break;
		case MENU::EXIT:
		{

		}
		break;
		}
	}

	if (KEY_MANAGER->isOnceKeyDown(VK_DOWN))
	{
		_selected = static_cast<MENU>(min(static_cast<UINT>(MENU::EXIT),static_cast<UINT>(_selected) + 1));
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_UP))
	{
		_selected = static_cast<MENU>(max(0, static_cast<int>(_selected) - 1));
	}



	
}

void MainScene::render()
{
	if (CONFIG_MANAGER->isActive())
	{
		CONFIG_MANAGER->render();
		return;
	}

	// background
	D2D_RENDERER->fillRectangle(FloatRect(0, 0, WINSIZEX, WINSIZEY), 106, 174, 247, 1);
	


	_backCloud->setScale(5);
	_backCloud->render(Vector2(_backX, WINSIZEY / 2), false);
	_backCloud->render(Vector2(_backX - _backCloud->getWidth() * 5, WINSIZEY / 2), false);
	_frontCloud->setScale(5);
	_frontCloud->render(Vector2(_frontX, WINSIZEY / 2), false);
	_frontCloud->render(Vector2(_frontX - _frontCloud->getWidth() * 5, WINSIZEY / 2), false);

	IMAGE_MANAGER->findImage("MAIN_SCENE/LOGO")->setScale(5);
	IMAGE_MANAGER->findImage("MAIN_SCENE/LOGO")->render(Vector2(WINSIZEX / 2, WINSIZEY / 2 - 180), false);

	IMAGE_MANAGER->findImage("MAIN_SCENE/COPYRIGHT")->setScale(4);
	IMAGE_MANAGER->findImage("MAIN_SCENE/COPYRIGHT")->render(Vector2(WINSIZEX / 2, WINSIZEY - 30), false);

	IMAGE_MANAGER->findImage("MAIN_SCENE/TEAM_LOGO")->render(Vector2(WINSIZEX - 120, WINSIZEY - 120), false);

	IMAGE_MANAGER->findImage(getImageName("MAIN_SCENE/PLAY", MENU::PLAY))->setScale(5);
	IMAGE_MANAGER->findImage(getImageName("MAIN_SCENE/PLAY", MENU::PLAY))->render(Vector2(WINSIZEX / 2, WINSIZEY / 2 + 160), false);
	IMAGE_MANAGER->findImage(getImageName("MAIN_SCENE/OPTION", MENU::OPTION))->setScale(5);
	IMAGE_MANAGER->findImage(getImageName("MAIN_SCENE/OPTION", MENU::OPTION))->render(Vector2(WINSIZEX / 2, WINSIZEY / 2 + 230), false);
	IMAGE_MANAGER->findImage(getImageName("MAIN_SCENE/EXIT", MENU::EXIT))->setScale(5);
	IMAGE_MANAGER->findImage(getImageName("MAIN_SCENE/EXIT", MENU::EXIT))->render(Vector2(WINSIZEX / 2, WINSIZEY / 2 + 300), false);

	_birdImage->setScale(5);
	_birdImage->aniRender(Vector2(WINSIZEX / 2 - 200, static_cast<int>(_selectedRc[static_cast<UINT>(_selected)].getCenter().y)), _birdAni, false);
	_birdImage->setScale(5);
	_birdImage->aniRender(Vector2(WINSIZEX / 2 + 200, static_cast<int>(_selectedRc[static_cast<UINT>(_selected)].getCenter().y)), _birdAni, true);

	if (DATA_MANAGER->isActive())
	{
		DATA_MANAGER->render();
		return;
	}

	IMAGE_MANAGER->findImage("CURSOR_BASIC")->setScale(5);
	IMAGE_MANAGER->findImage("CURSOR_BASIC")->render(Vector2(_ptMouse.x, _ptMouse.y));
}
