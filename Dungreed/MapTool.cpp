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

	if (KEY_MANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_save.ptInRect(_ptMouse)) save();
		if (_load.ptInRect(_ptMouse)) load();
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_F1))
	{
		paletteChange();
		
	}
}

void MapTool::render()
{
	_camera.render(IMAGE_MANAGER->findImage("Town_BGL"), Vector2(500, 500));

	Vector2 size = _paletteImage->getSize();
	size.x *= _paletteImage->getMaxFrameX();
	size.y *= _paletteImage->getMaxFrameY();
	
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

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		_paletteImage->setScale(2);
		//D2D_RENDERER->drawRectangle(_vTileMap[i].rc, D2D1::ColorF::Blue, 1, 0.5f);
		//_paletteImage->frameRender(_vTileMap[i].rc.getCenter(), _vTileMap[i].tileFrameX, _vTileMap[i].tileFrameY);
		//D2D_RENDERER->drawRectangle(_tile[i].rc, D2D1::ColorF::Blue, 1, 0.5f);
		_paletteImage->frameRender(_tile[i].rc.getCenter(), _tile[i].tileFrameX, _tile[i].tileFrameY);
	}

	wstring text(L"save");
	D2D_RENDERER->renderText(210, WINSIZEY - 100, text,30,D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING,L"µÕ±Ù¸ð²Ã",0.0f);
	D2D_RENDERER->drawRectangle(_save, D2D1::ColorF::Blue, 1, 0.5f);

	wstring text2(L"laod");
	D2D_RENDERER->renderText(410, WINSIZEY - 100, text2, 30, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);
	D2D_RENDERER->drawRectangle(_load, D2D1::ColorF::Blue, 1, 0.5f);

	wstring text3(L"erase");
	D2D_RENDERER->renderText(610, WINSIZEY - 100, text3, 30, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);
	D2D_RENDERER->drawRectangle(_erase, D2D1::ColorF::Blue, 1, 0.5f);

	wstring text4(L"Palette");
	D2D_RENDERER->renderText(610, WINSIZEY - 100, text3, 30, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);
	D2D_RENDERER->drawRectangle(_paletteLoad, D2D1::ColorF::Blue, 1, 0.5f);
}

void MapTool::setup()
{
	// _camera.setConfig(100, 100, )
	// _saveBtn = CreateWindow("button", "save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, WINSIZEX - 200,WINSIZEY- 200, 100,50, _hWnd, HMENU(0), _hInstance, NULL);
	_save = FloatRect(Vector2(200, WINSIZEY - 100), Vector2(100, 50), PIVOT::LEFT_TOP);
	_load = FloatRect(Vector2(400, WINSIZEY - 100), Vector2(100, 50), PIVOT::LEFT_TOP);
	_erase = FloatRect(Vector2(600, WINSIZEY - 100), Vector2(100, 50), PIVOT::LEFT_TOP);
	_paletteLoad=FloatRect(Vector2(1000, WINSIZEY - 100), Vector2(100, 50), PIVOT::LEFT_TOP);

	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[SAMPLETILEX * i + j].tileFrameX = j;
			_sampleTile[SAMPLETILEX * i + j].tileFrameY = i;
			_sampleTile[SAMPLETILEX * i + j].rc = FloatRect(Vector2(1196 + j * TILESIZE, 96 + TILESIZE * i), Vector2(32, 32), PIVOT::CENTER);
			
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
		//_vTileMap[i].tileFrameX = 0;
		//_vTileMap[i].tileFrameY = 0;
		_tile[i].tileFrameX = 0;
		_tile[i].tileFrameY = 0;
		_tile[i].linePos == DRAW_LINE_POSITION::NOLINE;
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

	WriteFile(stageFile, _tile, sizeof(tagTileMap) * TILEX * TILEY, &write, NULL);

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

	ReadFile(stageFile, _tile, sizeof(tagTileMap) * TILEX * TILEY, &read, NULL);

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
	
		ReadFile(stageFile, _tile, sizeof(tagTileMap) * TILEX * TILEY, &read, NULL);
	
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
	else _drawLinePos = DRAW_LINE_POSITION::NOLINE;
	/*if((frameX==6||frameX==8)&&frameY==7)_drawLinePos = DRAW_LINE_POSITION::LEFT_DIAGONAL;
	if ((frameX == 7 || frameX == 9) && frameY == 7)_drawLinePos = DRAW_LINE_POSITION::RIGHT_DIAGONAL;
	*/
}
