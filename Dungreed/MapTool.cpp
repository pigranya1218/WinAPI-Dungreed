#include "stdafx.h"
#include "MapTool.h"

HRESULT MapTool::init()
{
	// Default Tilemap Size Setting
	_tileX = 30;
	_tileY = 20;
	
	// 팔레트 그리기
	_paletteNum = 1;
	_paletteImage = IMAGE_MANAGER->findImage("sampleTile"+to_string(_paletteNum));
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[SAMPLETILEX * i + j].tileFrameX = j;
			_sampleTile[SAMPLETILEX * i + j].tileFrameY = i;
			_sampleTile[SAMPLETILEX * i + j].rc = FloatRect(Vector2(1196 + j * 32, 96 + 32 * i), Vector2(32, 32), PIVOT::CENTER);
		}
	}

	// 인터페이스 위치 설정
	_save = FloatRect(Vector2(200, WINSIZEY - 100), Vector2(100, 50), PIVOT::LEFT_TOP);
	_load = FloatRect(Vector2(400, WINSIZEY - 100), Vector2(100, 50), PIVOT::LEFT_TOP);
	_erase = FloatRect(Vector2(600, WINSIZEY - 100), Vector2(100, 50), PIVOT::LEFT_TOP);
	_layer1Btn = FloatRect(Vector2(800, WINSIZEY - 100), Vector2(100, 50), PIVOT::LEFT_TOP);
	_layer2Btn = FloatRect(Vector2(1000, WINSIZEY - 100), Vector2(100, 50), PIVOT::LEFT_TOP);

	_decreaseTileX = FloatRect(Vector2(300, WINSIZEY - 150), Vector2(20, 20), PIVOT::LEFT_TOP);
	_increaseTileX = FloatRect(Vector2(350, WINSIZEY - 150), Vector2(20, 20), PIVOT::LEFT_TOP);
	_decreaseTileY = FloatRect(Vector2(300, WINSIZEY - 200), Vector2(20, 20), PIVOT::LEFT_TOP);
	_increaseTileY = FloatRect(Vector2(350, WINSIZEY - 200), Vector2(20, 20), PIVOT::LEFT_TOP);

	_layer = 0;
	_selectDrag = false;
	_selectStart = Vector2(-1, -1);
	_selectEnd = Vector2(-1, -1);

	setup();
	return S_OK;
}

void MapTool::release()
{
}

void MapTool::update()
{
	if (KEY_MANAGER->isOnceKeyDown(VK_F1))
	{
		paletteChange();
	}

	setMap();

	if (KEY_MANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		setTileSize();
		if (_save.ptInRect(_ptMouse))
		{
			save();
		}
		else if (_load.ptInRect(_ptMouse))
		{
			load();
		}
		else if (_erase.ptInRect(_ptMouse))
		{
			load();
		}
		else if (_layer1Btn.ptInRect(_ptMouse))
		{
			_layer = 0; // 배경
		}
		else if (_layer2Btn.ptInRect(_ptMouse))
		{
			_layer = 1; // 이미지
		}
	}

	
	
	if (KEY_MANAGER->isStayKeyDown('D'))
	{
		CAMERA->movePivot(Vector2(10, 0));
	}
	if (KEY_MANAGER->isStayKeyDown('A'))
	{
		CAMERA->movePivot(Vector2(-10, 0));
	}
	if (KEY_MANAGER->isStayKeyDown('W'))
	{
		CAMERA->movePivot(Vector2(0, -10));
	}
	if (KEY_MANAGER->isStayKeyDown('S'))
	{
		CAMERA->movePivot(Vector2(0, 10));
	}
	
	// Exit
	if (KEY_MANAGER->isStayKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

}

void MapTool::render()
{
	for (int i = 0; i < _tileX * _tileY; ++i)
	{
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_tile[i].rc), D2D1::ColorF::Blue, 1, 0.5f);
		
		if (_tile[i].tileFrameX[0] != -1)
		{
			if (_layer != 0)
			{
				_paletteImage->setAlpha(0.5);
			}
			_paletteImage->setScale(4);
			CAMERA->frameRender(_paletteImage, _tile[i].rc.getCenter(), _tile[i].tileFrameX[0], _tile[i].tileFrameY[0]);
		}

		if (_tile[i].tileFrameX[1] != -1)
		{
			if (_layer != 1)
			{
				_paletteImage->setAlpha(0.5);
			}
			_paletteImage->setScale(4);
			CAMERA->frameRender(_paletteImage, _tile[i].rc.getCenter(), _tile[i].tileFrameX[1], _tile[i].tileFrameY[1]);
		}
	}

	FloatRect frame = FloatRect(Vector2(0, 640), Vector2(WINSIZEX, 960), PIVOT::LEFT_TOP);
	D2D_RENDERER->fillRectangle(frame, 255, 255, 255, 1, 0, Vector2(0, 0));
	FloatRect frame2 = FloatRect(Vector2(960, 0), Vector2(640, WINSIZEY), PIVOT::LEFT_TOP);
	D2D_RENDERER->fillRectangle(frame2, 255, 255, 255, 1, 0, Vector2(0, 0));

	
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_paletteImage->setScale(2);
			if (j >= _paletteImage->getMaxFrameX() || i >= _paletteImage->getMaxFrameY()) continue;
			else _paletteImage->frameRender( _sampleTile[SAMPLETILEX * i + j].rc.getCenter(), j, i);
		}
	}

	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
	{
		int xIndex = i % SAMPLETILEX;
		int yIndex = i / SAMPLETILEX;
		if (_selectStart.x <= xIndex && xIndex <= _selectEnd.x && _selectStart.y <= yIndex && yIndex <= _selectEnd.y)
		{
			D2D_RENDERER->drawRectangle(_sampleTile[i].rc, D2D1::ColorF::Red, 1, 3);
		}
		else
		{
			D2D_RENDERER->drawRectangle(_sampleTile[i].rc, D2D1::ColorF::Black, 1, 1);
		}
	}
	

	//인터페이스들 렌더
	D2D_RENDERER->renderText(210, WINSIZEY - 100, L"SAVE",30,D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING,L"둥근모꼴",0.0f);
	D2D_RENDERER->drawRectangle(_save, D2D1::ColorF::Blue, 1, 0.5f);

	D2D_RENDERER->renderText(410, WINSIZEY - 100, L"LOAD", 30, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.0f);
	D2D_RENDERER->drawRectangle(_load, D2D1::ColorF::Blue, 1, 0.5f);

	D2D_RENDERER->renderText(610, WINSIZEY - 100, L"ERASE", 30, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.0f);
	D2D_RENDERER->drawRectangle(_erase, D2D1::ColorF::Blue, 1, 0.5f);

	D2D_RENDERER->renderText(810, WINSIZEY - 100, L"LAYER1", 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.0f);
	D2D_RENDERER->drawRectangle(_layer1Btn, D2D1::ColorF::Blue, 1, 0.5f);

	D2D_RENDERER->renderText(1010, WINSIZEY - 100, L"LAYER2", 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.0f);
	D2D_RENDERER->drawRectangle(_layer2Btn, D2D1::ColorF::Blue, 1, 0.5f);

	D2D_RENDERER->renderText(_increaseTileX.right+50, _increaseTileX.getCenter().y, L"XUP", 10, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_CENTER, L"둥근모꼴", 0.0f);
	D2D_RENDERER->drawRectangle(_increaseTileX, D2D1::ColorF::Blue, 1, 0.5f);

	D2D_RENDERER->renderText((_decreaseTileX.right+ _decreaseTileX.left)/2+12 , _decreaseTileX.getCenter().y, L"X:" + to_wstring(_tileX), 10, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.0f);

	D2D_RENDERER->renderText(_decreaseTileX.left - 50, _decreaseTileX.getCenter().y, L"XDOWN", 10, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.0f);
	D2D_RENDERER->drawRectangle(_decreaseTileX, D2D1::ColorF::Blue, 1, 0.5f);

	D2D_RENDERER->renderText(_decreaseTileY.left - 50, _decreaseTileY.getCenter().y, L"YDOWN", 10, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.0f);
	D2D_RENDERER->drawRectangle(_decreaseTileY, D2D1::ColorF::Blue, 1, 0.5f);

	D2D_RENDERER->renderText((_decreaseTileY.right + _decreaseTileY.left) / 2 + 12, _decreaseTileY.getCenter().y, L"Y:" + to_wstring(_tileY), 10, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.0f);

	D2D_RENDERER->renderText(_increaseTileY.right + 50, _increaseTileY.getCenter().y, L"YUP", 10, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"둥근모꼴", 0.0f);
	D2D_RENDERER->drawRectangle(_increaseTileY, D2D1::ColorF::Blue, 1, 0.5f);
}

void MapTool::setup()
{
	CAMERA->setConfig(0, 0, 960, 640, 0, 0, max(0, TILESIZE * _tileX - 960), max(0, TILESIZE * _tileY - 640));

	// 타일맵 Rect 생성
	for (int i = 0; i < _tileY; ++i)
	{
		for (int j = 0; j < _tileX; ++j)
		{
			int index = _tileX * i + j;
			_tile[index].rc = FloatRect(Vector2(j * TILESIZE, i * TILESIZE), Vector2(TILESIZE, TILESIZE), PIVOT::LEFT_TOP);

			// 타일맵 초기화
			for (int layer = 0; layer <= 1; layer++)
			{
				_tile[index].tileFrameX[layer] = -1;
				_tile[index].tileFrameY[layer] = -1;
			}

			_tile[index].linePos == DRAW_LINE_POSITION::NOLINE;

			_tile[index].tileX = _tileX;
			_tile[index].tileY = _tileY;
		}
	}


}

void MapTool::setMap()
{
	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		// 팔레트에서 타일 선택
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
		{
			if (_sampleTile[i].rc.ptInRect(_ptMouse))
			{
				_selectStart.x = _sampleTile[i].tileFrameX;
				_selectStart.y = _sampleTile[i].tileFrameY;
				_selectDrag = true;
			}
		}
	}
	
	if (KEY_MANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_selectDrag)
		{
			_selectDrag = false;
		}
		
	}

	if (_selectDrag)
	{
		// 팔레트에서 타일 선택
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
		{
			if (_sampleTile[i].rc.ptInRect(_ptMouse))
			{
				_selectEnd.x = _sampleTile[i].tileFrameX;
				_selectEnd.y = _sampleTile[i].tileFrameY;
			}
		}
	}

	if (KEY_MANAGER->isStayKeyDown(VK_LBUTTON))
	{
		// 타일맵에 타일 그리기
		if (_ptMouse.x <= 960 && _ptMouse.y <= 640)
		{
			for (int i = 0; i < _tileX * _tileY; i++)
			{
				if (_tile[i].rc.ptInRect(CAMERA->getAbsolutePt(_ptMouse)))
				{
					for (int offsetX = 0; offsetX <= _selectEnd.x - _selectStart.x; offsetX++)
					{
						for (int offsetY = 0; offsetY <= _selectEnd.y - _selectStart.y; offsetY++)
						{
							int indexX = (i % _tileX) + offsetX;
							int indexY = (i / _tileX) + offsetY;
							if (indexY >= _tileY || indexX >= _tileX) continue;
							int index = indexY * _tileX + indexX;
							_tile[index].tileFrameX[_layer] = _selectStart.x + offsetX;
							_tile[index].tileFrameY[_layer] = _selectStart.y + offsetY;

							if (_layer == 1)
							{
								switch (_paletteNum)
								{
								case 1:
									
									if ((_tile[index].tileFrameX[_layer] == 6) && _tile[index].tileFrameY[_layer] == 7)_tile[index].linePos = DRAW_LINE_POSITION::LEFT_DIAGONAL;
									else if (( _tile[index].tileFrameX[_layer] == 8) && _tile[index].tileFrameY[_layer] == 7)_tile[index].linePos = DRAW_LINE_POSITION::PLATFORM_LEFT_DIAGONAL;
									else if ((_tile[index].tileFrameX[_layer] == 7) && _tile[index].tileFrameY[_layer] == 7)_tile[index].linePos = DRAW_LINE_POSITION::RIGHT_DIAGONAL;
									else if ((_tile[index].tileFrameX[_layer] == 9) && _tile[index].tileFrameY[_layer] == 7)_tile[index].linePos = DRAW_LINE_POSITION::PLATFORM_RIGHT_DIAGONAL;
									else if ((_tile[index].tileFrameX[_layer] >= 0 && _tile[index].tileFrameX[_layer] < 4) && _tile[index].tileFrameY[_layer] == 5)_tile[index].linePos = DRAW_LINE_POSITION::PLATFORM_TOP;
									else if ((_tile[index].tileFrameX[_layer] >= 5 && _tile[index].tileFrameX[_layer] < 8) && _tile[index].tileFrameY[_layer] == 5)_tile[index].linePos = DRAW_LINE_POSITION::PLATFORM_TOP;
									else _tile[index].linePos = DRAW_LINE_POSITION::BLOCK;
									break;
								case 2:
									
									 if ((_tile[index].tileFrameX[_layer] == 6 || _tile[index].tileFrameX[_layer] == 8) && _tile[index].tileFrameY[_layer] == 7)_tile[index].linePos = DRAW_LINE_POSITION::LEFT_DIAGONAL;
									else if ((_tile[index].tileFrameX[_layer] == 7 || _tile[index].tileFrameX[_layer] == 9) && _tile[index].tileFrameY[_layer] == 7)_tile[index].linePos = DRAW_LINE_POSITION::RIGHT_DIAGONAL;
									else if ((_tile[index].tileFrameX[_layer] >= 1 && _tile[index].tileFrameX[_layer] < 4) && _tile[index].tileFrameY[_layer] == 5)_tile[index].linePos = DRAW_LINE_POSITION::PLATFORM_TOP;
									
									else _tile[index].linePos = DRAW_LINE_POSITION::BLOCK;
									break;
									
								case 3:
									
									if ((_tile[index].tileFrameX[_layer] >= 0 && _tile[index].tileFrameX[_layer] < 4) && _tile[index].tileFrameY[_layer] == 5)_tile[index].linePos = DRAW_LINE_POSITION::PLATFORM_TOP;
									else if ((_tile[index].tileFrameX[_layer] >= 5 && _tile[index].tileFrameX[_layer] < 8) && _tile[index].tileFrameY[_layer] == 5)_tile[index].linePos = DRAW_LINE_POSITION::PLATFORM_TOP;
									else _tile[index].linePos = DRAW_LINE_POSITION::BLOCK;
									break;

								
								}


								
							}
						}
					}
					break;
				}
			}
		}
	}
}

void MapTool::save()
{
	ShowCursor(true);

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
	CloseHandle(stageFile);
	ShowCursor(false);
}

void MapTool::load()
{
	ShowCursor(true);

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
	ShowCursor(false);
	
	
}

void MapTool::paletteChange()
{
	_paletteNum++;
	if (_paletteNum > 3)_paletteNum = 1;
	_paletteImage=IMAGE_MANAGER->findImage("sampleTile" + to_string(_paletteNum));
	

	/*if (_paletteImage == IMAGE_MANAGER->findImage("sampleTile"))_paletteImage = IMAGE_MANAGER->findImage("sampleTile2");

	else if (_paletteImage == IMAGE_MANAGER->findImage("sampleTile2"))_paletteImage = IMAGE_MANAGER->findImage("sampleTile");*/
		
}

void MapTool::mapLoad()
{
	if (_vLoad.size() == 0) return;
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
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
	{
		if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_sampleTile[i].rc.ptInRect(_ptMouse))
			{
				_selectStart.x = _sampleTile[i].tileFrameX;
				_selectStart.y = _sampleTile[i].tileFrameY;
			}
		}
	}
}

void MapTool::setTileSize()
{
		if(_increaseTileX.ptInRect(_ptMouse))
		{
			if ((_tileX + 1)* _tileY >= MAXTILEX*MAXTILEY) return;
			_tileX += 1;
			setup();			
		}
		else if(_decreaseTileX.ptInRect(_ptMouse))
		{
			if (_tileX <= 1) return;
			_tileX -= 1;
			setup();
		}
		else if (_increaseTileY.ptInRect(_ptMouse))
		{
			if (_tileX* (_tileY + 1) >= MAXTILEX * MAXTILEY) return;
			_tileY += 1;
			setup();
		}
		else if (_decreaseTileY.ptInRect(_ptMouse))
		{
			if (_tileY <= 1) return;
			_tileY -= 1;
			setup();
		}
}
