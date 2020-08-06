#include "MapToolScene.h"
#include "tileMapNode.h"


HRESULT MapToolScene::init()
{
	_tileMapTool = new tileMapNode;
	_tileMapTool->init();

	return S_OK;
}

void MapToolScene::release()
{
}

void MapToolScene::update()
{
	_tileMapTool->update();
}

void MapToolScene::render()
{
	_tileMapTool->render();
}
