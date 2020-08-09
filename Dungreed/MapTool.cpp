#include "stdafx.h"
#include "MapTool.h"




HRESULT MapTool::init()
{
	_paletteImage = IMAGE_MANAGER->findImage("sampleTile");
	
	setup();

	return S_OK;
}

void MapTool::release()
{
}

void MapTool::update()
{
	setMap();
	
}

void MapTool::render()
{
	Vector2 size = _paletteImage->getSize();
	size.x *= _paletteImage->getMaxFrameX();
	size.y *= _paletteImage->getMaxFrameY();
	

	for (int i = 0; i < SAMPLETILEX*SAMPLETILEY; ++i)
	{
		CAMERA_MANAGER->rectangle(_sampleTile[i].rc, D2D1::ColorF::Red, 1, 0.5f);
	}
	
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_paletteImage->setScale(2);
			if (j >= _paletteImage->getMaxFrameX()||i>=_paletteImage->getMaxFrameY())continue;
			else CAMERA_MANAGER->frameRender(_paletteImage, _sampleTile[SAMPLETILEX*i + j].rc.getCenter(), j, i);
		}
	}

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		_paletteImage->setScale(2);
		CAMERA_MANAGER->rectangle(_vTileMap[i].rc, D2D1::ColorF::Blue, 1, 0.5f);
		_paletteImage->frameRender(_vTileMap[i].rc.getCenter(), _vTileMap[i].tileFrameX, _vTileMap[i].tileFrameY);
	}
	
	FloatRect temp = FloatRect(Vector2(WINSIZEX - 200, WINSIZEY - 200), Vector2(100, 50), PIVOT::LEFT_TOP);
	CAMERA_MANAGER->rectangle(temp, D2D1::ColorF::Blue, 1, 0.5f);
	
}

void MapTool::setup()
{
	_saveBtn = CreateWindow("button", "save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, WINSIZEX - 200,WINSIZEY- 200, 100,50, _hWnd, HMENU(0), _hInstance, NULL);


	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[SAMPLETILEX*i + j].tileFrameX = j;
			_sampleTile[SAMPLETILEX*i + j].tileFrameY = i;
			_sampleTile[SAMPLETILEX*i + j].rc = FloatRect(Vector2(1196+j*TILESIZE, 96+TILESIZE*i), Vector2(32, 32), PIVOT::CENTER);
		}
	}
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			_tile[TILEX*i + j].tileFrameX = j;
			_tile[TILEX*i + j].tileFrameY = i;
			_tile[TILEX*i + j].rc = FloatRect(Vector2(128 + j * TILESIZE, 96 + TILESIZE * i), Vector2(32, 32), PIVOT::CENTER);
			_vTileMap.push_back(_tile[TILEX * i + j]);
		}
	}

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		_vTileMap[i].tileFrameX = 0;
		_vTileMap[i].tileFrameY = 0;
	}

}

void MapTool::setMap()
{
	
	//setSelectTile();
	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
		{

			if (_sampleTile[i].rc.ptInRect(_ptMouse))
			{
				tagSelectTile _selectTile;
				_selectTile.x = _sampleTile[i].tileFrameX;
				_selectTile.y = _sampleTile[i].tileFrameY;
				_selectTile.rc = _sampleTile[i].rc;

				_vSelectTile.push_back(_selectTile);
			}

		}
	}
	if (KEY_MANAGER->isStayKeyDown(VK_LBUTTON))
	{
	    for (int i = 0; i < TILEX*TILEY; ++i)
	    {
		
			if (_tile[i].rc.ptInRect(_ptMouse))
			{
				for (int j=0;j<_vSelectTile.size();++j)
				{
					_vTileMap[i].tileFrameX = _vSelectTile[_vSelectTile.size()-1].x;
					_vTileMap[i].tileFrameY = _vSelectTile[_vSelectTile.size() - 1].y;
					releaseSelectTile();
					break;
				}
			}
		}
		
	}
}

void MapTool::save()
{
}

void MapTool::load()
{
}

void MapTool::setSelectTile()
{
	for (int i = 0; i < SAMPLETILEX*SAMPLETILEY; ++i)
	{
		if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_sampleTile[i].rc.ptInRect(_ptMouse))
			{
				tagSelectTile _selectTile;
				_selectTile.x = _sampleTile[i].tileFrameX;
				_selectTile.y = _sampleTile[i].tileFrameY;
				_selectTile.rc = _sampleTile[i].rc;

				_vSelectTile.push_back(_selectTile);
			}
		}
	}

}

void MapTool::releaseSelectTile()
{
	
}
