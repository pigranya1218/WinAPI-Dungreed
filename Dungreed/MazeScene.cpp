#include "stdafx.h"
#include "MazeScene.h"

HRESULT MazeScene::init()
{
	_size = 8;
	_stage.resize(_size);
	for (int i = 0; i < _size; i++)
	{
		_stage[i].resize(_size);
	}

	//while (true)
	//{
	//	for (int y = 0; y < _size; y++)
	//	{
	//		for (int x = 0; x < _size; x++)
	//		{
	//			_stage[x][y]._isVisited = false;
	//			for (int i = 0; i < 4; i++)
	//			{
	//				_stage[x][y]._isWall[i] = true;
	//			}
	//			_stage[x][y]._rc = FloatRect(Vector2(100 + x * 60, 100 + y * 60), Vector2(60, 60), PIVOT::LEFT_TOP);
	//		}
	//	}
	//	// 랜덤의 시작 지점을 잡고
	//	int startX = RANDOM->getInt(_size);
	//	int startY = RANDOM->getInt(_size);
	//	makeRoom(startX, startY);
	//	if (makeSpecialRoom()) // 시작방, 끝방, 식당, 상점을 만들 수 있는지 판단
	//	{
	//		break;
	//	}
	//}

	return S_OK;
}

void MazeScene::release()
{
}

void MazeScene::update()
{

	if (KEY_MANAGER->isOnceKeyDown('A'))
	{
		_start = make_pair(-1, -1);
		_end = make_pair(-1, -1);
		_restaurant = make_pair(-1, -1);
		_shop = make_pair(-1, -1);
		_notUse.clear();
		for (int y = 0; y < _size; y++)
		{
			for (int x = 0; x < _size; x++)
			{
				_stage[x][y]._isVisited = false;
				for (int i = 0; i < 4; i++)
				{
					_stage[x][y]._isWall[i] = true;
				}
				_stage[x][y]._rc = FloatRect(Vector2(100 + x * 60, 100 + y * 60), Vector2(60, 60), PIVOT::LEFT_TOP);
			}
		}
		// 랜덤의 시작 지점을 잡고
		int startX = RANDOM->getInt(_size);
		int startY = RANDOM->getInt(_size);
		makeRoom(startX, startY);
	}

	if (KEY_MANAGER->isOnceKeyDown('S'))
	{
		_start = make_pair(-1, -1);
		_end = make_pair(-1, -1);
		_restaurant = make_pair(-1, -1);
		_shop = make_pair(-1, -1);
		_notUse.clear();

		if (!makeSpecialRoom())
		{
			_start = make_pair(-1, -1);
			_end = make_pair(-1, -1);
			_restaurant = make_pair(-1, -1);
			_shop = make_pair(-1, -1);
			_notUse.clear();
		}
	}
}

void MazeScene::render()
{
	int move[4][4] = { {-1, 1, -1, -1}, {-1, -1, 1, -1}, {1, -1, 1, 1}, {1, 1, -1, 1} }; // L T R B

	for (int y = 0; y < _size; y++)
	{
		for (int x = 0; x < _size; x++)
		{
			int width = 30, height = 30;
			
			for (int i = 0; i < 4; i++)
			{
				if (_stage[x][y]._isWall[i])
				{
					Vector2 center = _stage[x][y]._rc.getCenter();
					Vector2 start = Vector2(center.x + width * move[i][0], center.y + height * move[i][1]);
					Vector2 end = Vector2(center.x + width * move[i][2], center.y + height * move[i][3]);
					D2D_RENDERER->drawLine(start, end);
				}
			}
		}
	}

	if (_shop.first != -1)
	{
		D2D_RENDERER->renderTextField(_stage[_start.first][_start.second]._rc.left, _stage[_start.first][_start.second]._rc.top, L"START", RGB(0, 0, 0), 15,
			_stage[_start.first][_start.second]._rc.getWidth(), _stage[_start.first][_start.second]._rc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Alagard");
		D2D_RENDERER->renderTextField(_stage[_end.first][_end.second]._rc.left, _stage[_end.first][_end.second]._rc.top, L"END", RGB(0, 0, 0), 15,
			_stage[_end.first][_end.second]._rc.getWidth(), _stage[_end.first][_end.second]._rc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Alagard");
		D2D_RENDERER->renderTextField(_stage[_restaurant.first][_restaurant.second]._rc.left, _stage[_restaurant.first][_restaurant.second]._rc.top, L"REST", RGB(0, 0, 0), 15,
			_stage[_restaurant.first][_restaurant.second]._rc.getWidth(), _stage[_restaurant.first][_restaurant.second]._rc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Alagard");
		D2D_RENDERER->renderTextField(_stage[_shop.first][_shop.second]._rc.left, _stage[_shop.first][_shop.second]._rc.top, L"SHOP", RGB(0, 0, 0), 15,
			_stage[_shop.first][_shop.second]._rc.getWidth(), _stage[_shop.first][_shop.second]._rc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Alagard");
	
		for (int i = 0; i < _notUse.size(); i++)
		{
			D2D_RENDERER->fillRectangle(_stage[_notUse[i].first][_notUse[i].second]._rc);

		}
	}
	
	
	
}

void MazeScene::makeRoom(int x, int y)
{
	_stage[x][y]._isVisited = true;

	int move[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} }; // L T R B
	bool checkDir[4] = { false, false, false, false };

	while (true)
	{
		if (checkDir[0] && checkDir[1] && checkDir[2] && checkDir[3])
		{
			break;
		}
		int dir = RANDOM->getInt(4);
		if (checkDir[dir]) continue;
		checkDir[dir] = true;

		int newX = x + move[dir][0];
		int newY = y + move[dir][1];

		if (newX < 0 || newX >= _size || newY < 0 || newY >= _size) // 범위를 벗어났다면
		{
			continue;
		}
		if (_stage[newX][newY]._isVisited) // 이미 방문한 곳이라면
		{
			continue;
		}

		_stage[x][y]._isWall[dir] = false; // 진행방향의 벽은 삭제
		_stage[newX][newY]._isWall[(dir + 2) % 4] = false; 

		makeRoom(newX, newY);
	}
}

bool MazeScene::makeSpecialRoom()
{
	// 시작점 만들기
	vector<pair<int, int>> candidate;
	for (int x = 0; x < _size; x++)
	{
		for (int y = 0; y < _size; y++)
		{
			if (_stage[x][y]._isWall[0] && _stage[x][y]._isWall[1] && !_stage[x][y]._isWall[2] && !_stage[x][y]._isWall[3]) // 우 하
			{
				candidate.push_back(make_pair(x, y));
			}
			else if (_stage[x][y]._isWall[0] && _stage[x][y]._isWall[1] && !_stage[x][y]._isWall[2] && _stage[x][y]._isWall[3]) // 우
			{
				candidate.push_back(make_pair(x, y));
			}
			else if (_stage[x][y]._isWall[0] && _stage[x][y]._isWall[1] && _stage[x][y]._isWall[2] && !_stage[x][y]._isWall[3]) // 하
			{
				candidate.push_back(make_pair(x, y));
			}
		}
	}

	if (candidate.size() == 0) return false;
	int random = RANDOM->getInt(candidate.size());
	_start = candidate[random];

	// 끝점 만들기
	candidate.clear();
	for (int x = 0; x < _size; x++)
	{
		for (int y = 0; y < _size; y++)
		{
			if (_start.first == x && _start.second == y) continue;
			if (!_stage[x][y]._isWall[0] && !_stage[x][y]._isWall[1] && _stage[x][y]._isWall[2] && _stage[x][y]._isWall[3]) // 좌 상
			{
				candidate.push_back(make_pair(x, y));
			}
			else if (!_stage[x][y]._isWall[0] && _stage[x][y]._isWall[1] && _stage[x][y]._isWall[2] && _stage[x][y]._isWall[3]) // 좌
			{
				candidate.push_back(make_pair(x, y));
			}
			else if (_stage[x][y]._isWall[0] && !_stage[x][y]._isWall[1] && _stage[x][y]._isWall[2] && _stage[x][y]._isWall[3]) // 상
			{
				candidate.push_back(make_pair(x, y));
			}
		}
	}

	if (candidate.size() == 0) return false;
	random = RANDOM->getInt(candidate.size());
	_end = candidate[random];



	// 식당 만들기
	candidate.clear();
	for (int x = 0; x < _size; x++)
	{
		for (int y = 0; y < _size; y++)
		{
			if (_start.first == x && _start.second == y) continue;
			if (_end.first == x && _end.second == y) continue;
			if (!_stage[x][y]._isWall[0] && _stage[x][y]._isWall[1] && !_stage[x][y]._isWall[2] && _stage[x][y]._isWall[3]) // 좌 우
			{
				candidate.push_back(make_pair(x, y));
			}
			else if (!_stage[x][y]._isWall[0] && _stage[x][y]._isWall[1] && _stage[x][y]._isWall[2] && _stage[x][y]._isWall[3]) // 좌
			{
				candidate.push_back(make_pair(x, y));
			}
			else if (_stage[x][y]._isWall[0] && _stage[x][y]._isWall[1] && !_stage[x][y]._isWall[2] && _stage[x][y]._isWall[3]) // 우
			{
				candidate.push_back(make_pair(x, y));
			}
		}
	}

	if (candidate.size() == 0) return false;
	random = RANDOM->getInt(candidate.size());
	_restaurant = candidate[random];

	// 상점 만들기
	candidate.clear();
	for (int x = 0; x < _size; x++)
	{
		for (int y = 0; y < _size; y++)
		{
			if (_start.first == x && _start.second == y) continue;
			if (_end.first == x && _end.second == y) continue;
			if (_restaurant.first == x && _restaurant.second == y) continue;
			if (!_stage[x][y]._isWall[0] && _stage[x][y]._isWall[1] && !_stage[x][y]._isWall[2] && _stage[x][y]._isWall[3]) // 좌 우
			{
				candidate.push_back(make_pair(x, y));
			}
			else if (!_stage[x][y]._isWall[0] && _stage[x][y]._isWall[1] && _stage[x][y]._isWall[2] && _stage[x][y]._isWall[3]) // 좌
			{
				candidate.push_back(make_pair(x, y));
			}
			else if (_stage[x][y]._isWall[0] && _stage[x][y]._isWall[1] && !_stage[x][y]._isWall[2] && _stage[x][y]._isWall[3]) // 우
			{
				candidate.push_back(make_pair(x, y));
			}
		}
	}

	if (candidate.size() == 0) return false;
	random = RANDOM->getInt(candidate.size());
	_shop = candidate[random];

	// 랜덤으로 끝방들 몇 개 지우기
	candidate.clear();
	for (int x = 0; x < _size; x++)
	{
		for (int y = 0; y < _size; y++)
		{
			if (_start.first == x && _start.second == y) continue;
			if (_end.first == x && _end.second == y) continue;
			if (_restaurant.first == x && _restaurant.second == y) continue;
			if (_shop.first == x && _shop.second == y) continue;
			if (!_stage[x][y]._isWall[0] && _stage[x][y]._isWall[1] && _stage[x][y]._isWall[2] && _stage[x][y]._isWall[3]) // 좌
			{
				candidate.push_back(make_pair(x, y));
			}
			else if (_stage[x][y]._isWall[0] && !_stage[x][y]._isWall[1] && _stage[x][y]._isWall[2] && _stage[x][y]._isWall[3]) //  상
			{
				candidate.push_back(make_pair(x, y));
			}
			else if (_stage[x][y]._isWall[0] && _stage[x][y]._isWall[1] && !_stage[x][y]._isWall[2] && _stage[x][y]._isWall[3]) //  우
			{
				candidate.push_back(make_pair(x, y));
			}
			else if (_stage[x][y]._isWall[0] && _stage[x][y]._isWall[1] && _stage[x][y]._isWall[2] && !_stage[x][y]._isWall[3]) //  하
			{
				candidate.push_back(make_pair(x, y));
			}
		}
	}
	
	for (int i = 0; i < candidate.size(); i++)
	{
		_notUse.push_back(candidate[i]);
	}

	return true;
}
