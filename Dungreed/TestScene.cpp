#include "stdafx.h"
#include "TestScene.h"
#include "Player.h"

HRESULT TestScene::init()
{
	_player = new Player;
	_player->init();

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
	_player->render();
}
