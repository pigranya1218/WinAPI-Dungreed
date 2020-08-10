#include "stdafx.h"
#include "TestScene.h"
#include "Player.h"


HRESULT TestScene::init()
{
	



	_player = new Player;
	_player->init();
	// _player->setTestScene(this);
	setPlayer(_player);
	

	



	_item = IMAGE_MANAGER->findImage("ShortSpear");

	//지형 세팅
	_center = Vector2(WINSIZEX / 2, WINSIZEY - 50);
	_size = Vector2(WINSIZEX, 100);
	_ground = rectMakePivot(_center, _size, PIVOT::CENTER);

	return S_OK;
}

void TestScene::release()
{
	_player->release();
}

void TestScene::update()
{
	if (KEY_MANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	// _player->update();
}

void TestScene::render()
{
	IMAGE_MANAGER->findImage("Town_BGL")->setScale(5);
	_camera.render(IMAGE_MANAGER->findImage("Town_BGL"), Vector2(WINSIZEX / 2, WINSIZEY / 2));
	IMAGE_MANAGER->findImage("Town_BG")->setScale(5);
	_camera.render(IMAGE_MANAGER->findImage("Town_BG"), Vector2(WINSIZEX / 2, WINSIZEY / 2 + 200));
	IMAGE_MANAGER->findImage("Town_BG2")->setScale(5);
	_camera.render(IMAGE_MANAGER->findImage("Town_BG2"), Vector2(WINSIZEX / 2, WINSIZEY / 2 + 200));

	D2D_RENDERER->drawRectangle(_ground, D2D1::ColorF::Magenta, 1, 1);



	
	_player->render();
	
	IMAGE_MANAGER->findImage("CURSOR_SHOOTING")->setScale(4);
	IMAGE_MANAGER->findImage("CURSOR_SHOOTING")->render(Vector2(_ptMouse.x, _ptMouse.y));
}


