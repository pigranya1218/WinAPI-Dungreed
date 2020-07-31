#include "stdafx.h"
#include "MainScene.h"

HRESULT MainScene::init()
{
	_birdImage = IMAGE_MANAGER->findImage("MAIN_SCENE/BIRD");
	_ani = new Animation;
	_ani->init(_birdImage->getWidth(), _birdImage->getHeight(), _birdImage->getMaxFrameX(), _birdImage->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(20);
	_ani->start();
	
	_frontCloud = IMAGE_MANAGER->findImage("MAIN_SCENE/FRONT_CLOUD");
	_frontSpeed = 2;
	_backCloud = IMAGE_MANAGER->findImage("MAIN_SCENE/BACK_CLOUD");
	_backSpeed = 1;

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
	
	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
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

	IMAGE_MANAGER->findImage("MAIN_SCENE/PLAY_ON")->render(Vector2(WINSIZEX / 2, WINSIZEY / 2 + 180), false);
	IMAGE_MANAGER->findImage("MAIN_SCENE/OPTION_OFF")->render(Vector2(WINSIZEX / 2, WINSIZEY / 2 + 250), false);
	IMAGE_MANAGER->findImage("MAIN_SCENE/EXIT_OFF")->render(Vector2(WINSIZEX / 2, WINSIZEY / 2 + 320), false);

	_birdImage->setScale(6);
	_birdImage->aniRender(Vector2(WINSIZEX / 2 - 200, WINSIZEY / 2 + 180), _ani, false);
	_birdImage->setScale(6);
	_birdImage->aniRender(Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2 + 180), _ani, true);
}
