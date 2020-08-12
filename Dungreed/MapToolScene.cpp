#include "stdafx.h"
#include "MapToolScene.h"
#include "MapTool.h"


HRESULT MapToolScene::init()
{
	_tileMapTool = new MapTool;
	_tileMapTool->init();
	//CAMERA->setConfig(100, 50, 960, 640, 0, 0, 1600, 900);
	

	return S_OK;
}

void MapToolScene::release()
{
	_tileMapTool->release();
}

void MapToolScene::update()
{
	_tileMapTool->update();
}

void MapToolScene::render()
{

	_tileMapTool->render();

	IMAGE_MANAGER->findImage("CURSOR_BASIC")->setScale(5);
	IMAGE_MANAGER->findImage("CURSOR_BASIC")->render(Vector2(_ptMouse.x, _ptMouse.y));
}
