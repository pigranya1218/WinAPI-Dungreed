#include "stdafx.h"
#include "TestScene.h"
#include "Player.h"

HRESULT TestScene::init()
{
	_player = new Player;
	_player->init();
	_player->setTestScene(this);
	setPlayer(_player);

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
	_player->update();
}

void TestScene::render()
{
	//CAMERA_MANAGER->rectangle(_ground, D2D1::ColorF::Magenta, 1, 1);
	IMAGE_MANAGER->findImage("CURSOR_SHOOTING")->setScale(5);
	IMAGE_MANAGER->findImage("CURSOR_SHOOTING")->render(Vector2(_ptMouse.x, _ptMouse.y));
	_player->render();
}
