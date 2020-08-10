#include "stdafx.h"
#include "TestScene.h"
#include "Player.h"
#include "Item.h"
#include "Matchlock.h"

HRESULT TestScene::init()
{
	_player = new Player;
	_player->init();
	_player->setTestScene(this);
	setPlayer(_player);

	/*_item = new Item(_player->getPosition(), _player->getDirection());
	_item->init();
	_item->setTestScene(this);
	setItem(_item);*/
	
	/*_matchlock = new Matchlock(_player->getPosition(), _player->getDirection());
	_matchlock->init();
	_matchlock->setTestScene(this);
	setItem(_matchlock);*/

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

	_player->update();
	//_matchlock->update(_player->getPosition(), _player->getDirection());
}

void TestScene::render()
{
	D2D_RENDERER->drawRectangle(_ground, D2D1::ColorF::Magenta, 1, 1);
	
	_player->render();
	//_matchlock->render();
	
	IMAGE_MANAGER->findImage("CURSOR_SHOOTING")->setScale(4);
	IMAGE_MANAGER->findImage("CURSOR_SHOOTING")->render(Vector2(_ptMouse.x, _ptMouse.y));
}
