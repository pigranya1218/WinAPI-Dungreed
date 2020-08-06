#include "tileMapNode.h"




HRESULT tileMapNode::init()
{


	return S_OK;
}

void tileMapNode::release()
{
}

void tileMapNode::update()
{

	setup();
}

void tileMapNode::render()
{
	IMAGE_MANAGER->findImage("smapleTile")->render(Vector2(WINSIZEX- IMAGE_MANAGER->findImage("smapleTile")->getWidth(), 0), false);

	
}

void tileMapNode::setup()
{
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTile[i*SAMPLETILEX + j].paletteFrameX = j;
			_sampleTile[i*SAMPLETILEX + j].paletteFrameY = i;

			SetRect(&_sampleTile[i*SAMPLETILEX + j].rc, WINSIZEX - IMAGE_MANAGER->findImage("smapleTile")->getWidth() + TILESIZE * j,
				TILESIZE*i, WINSIZEX - IMAGE_MANAGER->findImage("smapleTile")->getWidth() + TILESIZE * j + TILESIZE,
				TILESIZE*i + TILESIZE);
		}
	}

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			SetRect(&_tile[i*TILEX + j].rc,
				j*TILESIZE,
				i*TILESIZE,
				j*TILESIZE + TILESIZE,
				i*TILESIZE + TILESIZE);
		}
	}
	for (int i = 0; i < TILEX*TILEY; i++)
	{
		_tile[i].tileFrameX = 4;
		_tile[i].tileFrameY = 3;
	}
}

void tileMapNode::setMap()
{
}

void tileMapNode::save()
{
}

void tileMapNode::load()
{
}
