#include "stdafx.h"
#include "MazeScene.h"

HRESULT MazeScene::init()
{
	_stage.resize(5);
	for (int i = 0; i < 5; i++)
	{
		_stage[i].resize(5);
	}

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			_stage[x][y]._isVisited = false;
			for (int i = 0; i < 4; i++)
			{
				_stage[x][y]._isWall[i] = true;
			}
			_stage[x][y]._rc = FloatRect(Vector2(x * 60, y * 60), Vector2(60, 60), PIVOT::LEFT_TOP);
		}
	}


	return S_OK;
}

void MazeScene::release()
{
}

void MazeScene::update()
{

}

void MazeScene::render()
{

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (_stage[x][y]._isWall[i])
				{
					Vector2 start;
					Vector2 end;
					D2D_RENDERER->drawLine(start, end);
				}
			}
		}
	}
}
