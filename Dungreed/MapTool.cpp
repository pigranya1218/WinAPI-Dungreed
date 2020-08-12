#include "stdafx.h"
#include "MapTool.h"

HRESULT MapTool::init()
{
	_tileX = 30;
	_tileY = 20;
	
	_paletteImage = IMAGE_MANAGER->findImage("sampleTile");
	setup();
	CAMERA->setConfig(0, 0, 960, 640, 0, 0, 0, 0);

	return S_OK;
}

void MapTool::release()
{
}

void MapTool::update()
{
	
	setMap();

	if (KEY_MANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		setTileSize();
		if (_save.ptInRect(_ptMouse)) save();
		if (_load.ptInRect(_ptMouse)) load();
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_F1))
	{
		paletteChange();
		
	}
	
	if (KEY_MANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERA->movePivot(Vector2(-2, 0));
		//_mapPointer.x += 1;
		for (int i = 0; i < _tileX*_tileY; i++)
		{
			_tile[i].rc.move(Vector2(-2,0));
			
		}
	}
	if (KEY_MANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERA->movePivot(Vector2(2, 0));
		//_mapPointer.x -= 1;
		for (int i = 0; i < _tileX*_tileY; i++)
		{
			_tile[i].rc.move(Vector2(2, 0));
			
		}
	}
	if (KEY_MANAGER->isStayKeyDown(VK_UP))
	{
		CAMERA->movePivot(Vector2(0, 2));
		//_mapPointer.y -= 1;
		for (int i = 0; i < _tileX*_tileY; i++)
		{
			_tile[i].rc.move(Vector2(0, 2));
			
		}
	}
	if (KEY_MANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERA->movePivot(Vector2(0, -2));
		//_mapPointer.y += 1;
		for (int i = 0; i < _tileX*_tileY; i++)
		{
			_tile[i].rc.move(Vector2(0, -2));
			
		}
	}

	

	// CAMERA->setXY(_tile[_tileX*_tileY/2].rc.getCenter());
	// CAMERA->setLT(_tile[0].rc.getCenter());
}

void MapTool::render()
{
	Vector2 size = _paletteImage->getSize();
	size.x *= _paletteImage->getMaxFrameX();
	size.y *= _paletteImage->getMaxFrameY();

	for (int i = 0; i < _tileX*_tileY; ++i)
	{
		_paletteImage->setScale(4);
		//D2D_RENDERER->drawRectangle(_vTileMap[i].rc, D2D1::ColorF::Blue, 1, 0.5f);
		//_paletteImage->frameRender(_vTileMap[i].rc.getCenter(), _vTileMap[i].tileFrameX, _vTileMap[i].tileFrameY);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_tile[i].rc), D2D1::ColorF::Blue, 1, 0.5f);
		//_paletteImage->frameRender(_tile[i].rc.getCenter(), _tile[i].tileFrameX, _tile[i].tileFrameY);
		CAMERA->frameRender(_paletteImage, _tile[i].rc.getCenter(), _tile[i].tileFrameX, _tile[i].tileFrameY);



		//D2D_RENDERER->drawEllipse(_mapPointer, 5, D2DRenderer::DefaultBrush::Red, 1);
	}

	//CAMERA->render(IMAGE_MANAGER->findImage("Town_BGL"), Vector2(500, 500));

	FloatRect frame = FloatRect(Vector2(0, 640), Vector2(WINSIZEX, 960), PIVOT::LEFT_TOP);
	D2D_RENDERER->fillRectangle(frame, 255, 255, 255, 1, 0, Vector2(0, 0));
	FloatRect frame2 = FloatRect(Vector2(960, 0), Vector2(640, WINSIZEY), PIVOT::LEFT_TOP);
	D2D_RENDERER->fillRectangle(frame2, 255, 255, 255, 1, 0, Vector2(0, 0));

	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
	{
		D2D_RENDERER->drawRectangle(_sampleTile[i].rc, D2D1::ColorF::Red, 1, 0.5f);
	}
	
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_paletteImage->setScale(2);
			if (j >= _paletteImage->getMaxFrameX() || i >= _paletteImage->getMaxFrameY()) continue;
			else _paletteImage->frameRender( _sampleTile[SAMPLETILEX * i + j].rc.getCenter(), j, i);
		}
	}

	


	//ÀÎÅÍÆäÀÌ½ºµé ·»´õ
	wstring text(L"save");
	D2D_RENDERER->renderText(210, WINSIZEY - 100, text,30,D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING,L"µÕ±Ù¸ð²Ã",0.0f);
	D2D_RENDERER->drawRectangle(_save, D2D1::ColorF::Blue, 1, 0.5f);

	wstring text2(L"laod");
	D2D_RENDERER->renderText(410, WINSIZEY - 100, text2, 30, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);
	D2D_RENDERER->drawRectangle(_load, D2D1::ColorF::Blue, 1, 0.5f);

	wstring text3(L"erase");
	D2D_RENDERER->renderText(610, WINSIZEY - 100, text3, 30, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);
	D2D_RENDERER->drawRectangle(_erase, D2D1::ColorF::Blue, 1, 0.5f);

	/*wstring text4(L"Palette");
	D2D_RENDERER->renderText(810, WINSIZEY - 100, WINSIZEY - 100, text4, 30, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);
	D2D_RENDERER->drawRectangle(_paletteLoad, D2D1::ColorF::Blue, 1, 0.5f);*/

	wstring text5(L"XUP");
	D2D_RENDERER->renderText(_increaseTileX.right+50, _increaseTileX.getCenter().y, text5, 10, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"µÕ±Ù¸ð²Ã", 0.0f);
	D2D_RENDERER->drawRectangle(_increaseTileX, D2D1::ColorF::Blue, 1, 0.5f);

	wstring text9(L"X:"+to_wstring( _tileX));
	D2D_RENDERER->renderText((_decreaseTileX.right+ _decreaseTileX.left)/2+12 , _decreaseTileX.getCenter().y, text9, 10, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);

	wstring text6(L"XDOWN");
	D2D_RENDERER->renderText(_decreaseTileX.left - 50, _decreaseTileX.getCenter().y, text6, 10, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);
	D2D_RENDERER->drawRectangle(_decreaseTileX, D2D1::ColorF::Blue, 1, 0.5f);

	wstring text7(L"YDOWN");
	D2D_RENDERER->renderText(_decreaseTileY.left - 50, _decreaseTileY.getCenter().y, text7, 10, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);
	D2D_RENDERER->drawRectangle(_decreaseTileY, D2D1::ColorF::Blue, 1, 0.5f);

	wstring text10(L"Y:" + to_wstring(_tileY));
	D2D_RENDERER->renderText((_decreaseTileY.right + _decreaseTileY.left) / 2 + 12, _decreaseTileY.getCenter().y, text10, 10, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);


	wstring text8(L"YUP");
	D2D_RENDERER->renderText(_increaseTileY.right + 50, _increaseTileY.getCenter().y, text8, 10, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);
	D2D_RENDERER->drawRectangle(_increaseTileY, D2D1::ColorF::Blue, 1, 0.5f);
}

void MapTool::setup()
{
	// _camera.setConfig(100, 100, )
	// _saveBtn = CreateWindow("button", "save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, WINSIZEX - 200,WINSIZEY- 200, 100,50, _hWnd, HMENU(0), _hInstance, NULL);
	_save = FloatRect(Vector2(200, WINSIZEY - 100), Vector2(100, 50), PIVOT::LEFT_TOP);
	_load = FloatRect(Vector2(400, WINSIZEY - 100), Vector2(100, 50), PIVOT::LEFT_TOP);
	_erase = FloatRect(Vector2(600, WINSIZEY - 100), Vector2(100, 50), PIVOT::LEFT_TOP);
	_paletteLoad=FloatRect(Vector2(1000, WINSIZEY - 100), Vector2(100, 50), PIVOT::LEFT_TOP);
	_decreaseTileX = FloatRect(Vector2(300, WINSIZEY - 150), Vector2(20, 20), PIVOT::LEFT_TOP);
	_increaseTileX = FloatRect(Vector2(350, WINSIZEY - 150), Vector2(20, 20), PIVOT::LEFT_TOP);
	_decreaseTileY = FloatRect(Vector2(300, WINSIZEY - 200), Vector2(20, 20), PIVOT::LEFT_TOP);
	_increaseTileY = FloatRect(Vector2(350, WINSIZEY - 200), Vector2(20, 20), PIVOT::LEFT_TOP);


	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[SAMPLETILEX * i + j].tileFrameX = j;
			_sampleTile[SAMPLETILEX * i + j].tileFrameY = i;
			_sampleTile[SAMPLETILEX * i + j].rc = FloatRect(Vector2(1196 + j * 32, 96 + 32 * i), Vector2(32, 32), PIVOT::CENTER);
			
		}
	}

	

	for (int i = 0; i < _tileY; ++i)
	{
		for (int j = 0; j < _tileX; ++j)
		{
			_tile[_tileX*i + j].tileFrameX = j;
			_tile[_tileX*i + j].tileFrameY = i;
			_tile[_tileX*i + j].rc = FloatRect(Vector2(16+ j * TILESIZE, +16+ TILESIZE * i), Vector2(TILESIZE, TILESIZE), PIVOT::CENTER);
			_vTileMap.push_back(_tile[_tileX * i + j]);
		}
	}

	for (int i = 0; i < _tileX*_tileY; ++i)
	{
		//_vTileMap[i].tileFrameX = 0;
		//_vTileMap[i].tileFrameY = 0;
		_tile[i].tileFrameX = 0;
		_tile[i].tileFrameY = 0;
		_tile[i].linePos == DRAW_LINE_POSITION::NOLINE;
		
		_map[0].Tx = _tileX;
		_map[0].Ty = _tileY;
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
	    for (int i = 0; i < _tileX*_tileY; ++i)
	    {
			if (_tile[i].rc.ptInRect(_ptMouse)&& _ptMouse.x<=960&&_ptMouse.y<=640)
			{
				for (int j = 0; j < _vSelectTile.size(); ++j)
				{
					_tile[i].tileFrameX = _vSelectTile[_vSelectTile.size() - 1].x;
					_tile[i].tileFrameY = _vSelectTile[_vSelectTile.size() - 1].y;
					//setLinePos(_tile[i].tileFrameX, _tile[i].tileFrameY);
					//_tile[i].linePos = _drawLinePos;

					if (_tile[i].tileFrameX == 1 && _tile[i].tileFrameY == 8)_tile[i].linePos = DRAW_LINE_POSITION::TOP;
					if (_tile[i].tileFrameX == 1 && _tile[i].tileFrameY == 6)_tile[i].linePos = DRAW_LINE_POSITION::BOTTOM;
					if (_tile[i].tileFrameX == 2 && _tile[i].tileFrameY == 7)_tile[i].linePos = DRAW_LINE_POSITION::LEFT;
					if (_tile[i].tileFrameX == 0 && _tile[i].tileFrameY == 7)_tile[i].linePos = DRAW_LINE_POSITION::RIGHT;
					if ((_tile[i].tileFrameX == 6|| _tile[i].tileFrameX == 8) && _tile[i].tileFrameY == 7)_tile[i].linePos = DRAW_LINE_POSITION::LEFT_DIAGONAL;
					if ((_tile[i].tileFrameX == 7|| _tile[i].tileFrameX == 9) && _tile[i].tileFrameY == 7)_tile[i].linePos = DRAW_LINE_POSITION::RIGHT_DIAGONAL;
					else _tile[i].linePos == DRAW_LINE_POSITION::NOLINE;

					releaseSelectTile();
					break;
				}
			}
			/*if (_tile[i].rc.ptInRect(_ptMouse))
			{
				for (int j=0;j<_vSelectTile.size();++j)
				{
					_vTileMap[i].tileFrameX = _vSelectTile[_vSelectTile.size()-1].x;
					_vTileMap[i].tileFrameY = _vSelectTile[_vSelectTile.size() - 1].y;
					releaseSelectTile();
					break;
				}
			}*/
		}
		
	}
}

void MapTool::save()
{
	
	SetCursor;

	TCHAR szFile[260] = _T("");
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = _T("map Files(*.map)\0*.map\0All Files (*.*)\0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_OVERWRITEPROMPT;
	if (::GetSaveFileName(&ofn) == false) return;

	TCHAR* return_path = ofn.lpstrFile;

	

	HANDLE stageFile;
	DWORD write;

	stageFile = CreateFile(ofn.lpstrFile, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(stageFile, _tile, sizeof(tagTileMap) * _tileX * _tileY, &write, NULL);
	WriteFile(stageFile, _map, sizeof(tagMap), &write, NULL);

	CloseHandle(stageFile);

}

void MapTool::load()
{
	TCHAR szFilePath[MAX_PATH] = { 0, };
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.nMaxFile = sizeof(szFilePath);
	ofn.lpstrFilter = _T("map Files(*.map)\0*.map\0All Files (*.*)\0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (::GetOpenFileName(&ofn) == false) return;
	TCHAR* return_path = ofn.lpstrFile;

	HANDLE stageFile;
	DWORD read;

	stageFile = CreateFile(ofn.lpstrFile, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(stageFile, _tile, sizeof(tagTileMap) * _tileX * _tileY, &read, NULL);

	CloseHandle(stageFile);
}

void MapTool::paletteChange()
{
	/*TCHAR szFilePath[MAX_PATH] = {0,};
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.nMaxFile=	sizeof(szFilePath);
	ofn.lpstrFilter = _T("png Files(*.png)\0*.png\0All Files (*.*)\0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (::GetOpenFileName(&ofn) == false) return;
	TCHAR* return_path = ofn.lpstrFile;*/
	
	if (_paletteImage == IMAGE_MANAGER->findImage("sampleTile"))_paletteImage = IMAGE_MANAGER->findImage("sampleTile2");

	else if (_paletteImage == IMAGE_MANAGER->findImage("sampleTile2"))_paletteImage = IMAGE_MANAGER->findImage("sampleTile");
		
}

void MapTool::mapLoad()
{
	if (_vLoad.size() == 0)return;
	HANDLE stageFile;
	DWORD read;
	
	for (int i = 0; i < _vLoad.size(); ++i)
	{
		stageFile = CreateFile(_vLoad[i], GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
		ReadFile(stageFile, _tile, sizeof(tagTileMap) * _tileX * _tileY, &read, NULL);
	
		CloseHandle(stageFile);
	}
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

void MapTool::setLinePos(int frameX, int frameY)
{
	if (frameX == 1 && frameY == 8)_drawLinePos=DRAW_LINE_POSITION::TOP;
	if(frameX==1 && frameY==6)_drawLinePos = DRAW_LINE_POSITION::BOTTOM;
	if(frameX==0 && frameY==7)_drawLinePos = DRAW_LINE_POSITION::RIGHT;
	if(frameX==2 && frameY==7)_drawLinePos = DRAW_LINE_POSITION::LEFT;
	if ((frameX >=0&&frameX<4)&&frameY==5 )_drawLinePos = DRAW_LINE_POSITION::PLATFORM;
	if ((frameX >= 5 && frameX < 8) && frameY == 5)_drawLinePos = DRAW_LINE_POSITION::PLATFORM;
	else _drawLinePos = DRAW_LINE_POSITION::NOLINE;
	/*if((frameX==6||frameX==8)&&frameY==7)_drawLinePos = DRAW_LINE_POSITION::LEFT_DIAGONAL;
	if ((frameX == 7 || frameX == 9) && frameY == 7)_drawLinePos = DRAW_LINE_POSITION::RIGHT_DIAGONAL;
	*/
}

void MapTool::setTileSize()
{
	

		if(_increaseTileX.ptInRect(_ptMouse))
		{
			if (_tileX* _tileY >= 1900) return;
			_tileX += 1;
			setup();
		}
		else if(_decreaseTileX.ptInRect(_ptMouse))
		{
			
			_tileX -= 1;
			setup();
		}
		else if (_increaseTileY.ptInRect(_ptMouse))
		{
			if (_tileX* _tileY >= 1900) return;
			_tileY += 1;
			setup();
		}
		else if (_decreaseTileY.ptInRect(_ptMouse))
		{
			_tileY -= 1;
			setup();
		}
	


}
