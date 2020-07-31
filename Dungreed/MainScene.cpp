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
	return S_OK;
}

void MainScene::release()
{
}

void MainScene::update()
{
	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
}

void MainScene::render()
{
	D2D_RENDERER->fillRectangle(FloatRect(0, 0, WINSIZEX, WINSIZEY), 106, 174, 247, 1);

	IMAGE_MANAGER->findImage("MAIN_SCENE/LOGO")->setScale(3);
	IMAGE_MANAGER->findImage("MAIN_SCENE/LOGO")->render(Vector2(WINSIZEX / 2, WINSIZEY / 2 - 200), false);
	IMAGE_MANAGER->findImage("MAIN_SCENE/LOGO")->setScale(3);
	IMAGE_MANAGER->findImage("MAIN_SCENE/LOGO")->render(Vector2(WINSIZEX / 2, WINSIZEY / 2), true);

	_birdImage->setScale(3);
	_birdImage->aniRender(Vector2(WINSIZEX / 2 - 200, WINSIZEY / 2 + 200), _ani, false);
	_birdImage->setScale(3);
	_birdImage->aniRender(Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2 + 200), _ani, true);
}
