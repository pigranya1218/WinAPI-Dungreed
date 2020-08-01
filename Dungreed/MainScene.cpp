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

	_selected = MENU::PLAY;
	for (int i = 0; i < static_cast<UINT>(MENU::END); i++)
	{
		int posY = WINSIZEY / 2 + 180 + i * 70;
		_selectedRc[i] = FloatRect(Vector2(WINSIZEX / 2, posY), Vector2(300, 70), PIVOT::CENTER);
	}

	return S_OK;
}

void MainScene::release()
{
}

void MainScene::update()
{
	_frontX += _frontSpeed;
	if (_frontX >= _frontCloud->getWidth())
	{
		_frontX -= _frontCloud->getWidth();
	}
	_backX += _backSpeed;
	if (_backX >= _backCloud->getWidth())
	{
		_backX -= _backCloud->getWidth();
	}

	if (KEY_MANAGER->isOnceKeyDown(VK_DOWN))
	{
		_selected = static_cast<MENU>(min(static_cast<UINT>(MENU::EXIT),static_cast<UINT>(_selected) + 1));
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_UP))
	{
		_selected = static_cast<MENU>(max(0, static_cast<UINT>(_selected) - 1));
	}
	
	_birdAni->frameUpdate(TIME_MANAGER->getElapsedTime());
}

void MainScene::render()
{
	// background
	D2D_RENDERER->fillRectangle(FloatRect(0, 0, WINSIZEX, WINSIZEY), 106, 174, 247, 1);
	_backCloud->render(Vector2(_backX, WINSIZEY / 2), false);
	_backCloud->render(Vector2(_backX - _backCloud->getWidth(), WINSIZEY / 2), false);
	_frontCloud->render(Vector2(_frontX, WINSIZEY / 2), false);
	_frontCloud->render(Vector2(_frontX - _frontCloud->getWidth(), WINSIZEY / 2), false);

	IMAGE_MANAGER->findImage("MAIN_SCENE/LOGO")->render(Vector2(WINSIZEX / 2, WINSIZEY / 2 - 180), false);

	IMAGE_MANAGER->findImage("MAIN_SCENE/COPYRIGHT")->render(Vector2(WINSIZEX / 2, WINSIZEY - 25), false);

	IMAGE_MANAGER->findImage("MAIN_SCENE/TEAM_LOGO")->render(Vector2(WINSIZEX - 120, WINSIZEY - 120), false);

	IMAGE_MANAGER->findImage(getImageName("MAIN_SCENE/PLAY", MENU::PLAY))->render(Vector2(WINSIZEX / 2, WINSIZEY / 2 + 180), false);
	IMAGE_MANAGER->findImage(getImageName("MAIN_SCENE/OPTION", MENU::OPTION))->render(Vector2(WINSIZEX / 2, WINSIZEY / 2 + 250), false);
	IMAGE_MANAGER->findImage(getImageName("MAIN_SCENE/EXIT", MENU::EXIT))->render(Vector2(WINSIZEX / 2, WINSIZEY / 2 + 320), false);

	_birdImage->setScale(6);
	_birdImage->aniRender(Vector2(WINSIZEX / 2 - 200, static_cast<int>(_selectedRc[static_cast<UINT>(_selected)].getCenter().y)), _birdAni, false);
	_birdImage->setScale(6);
	_birdImage->aniRender(Vector2(WINSIZEX / 2 + 200, static_cast<int>(_selectedRc[static_cast<UINT>(_selected)].getCenter().y)), _birdAni, true);
}
