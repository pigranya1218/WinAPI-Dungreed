#include "TestStage.h"

void TestStage::init()
{
	Stage::init();
	_collisions.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(0, 800), Vector2(WINSIZEX, 800)), LINEAR_VALUE_TYPE::DOWN });
	_collisions.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(50, 100), Vector2(50, 800)), LINEAR_VALUE_TYPE::LEFT });
	_collisions.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(1550, 100), Vector2(1550, 800)), LINEAR_VALUE_TYPE::RIGHT });

	_tileImage = IMAGE_MANAGER->findImage("sampleTile");
	mapLoad();


	int curr = 0;
	
	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		switch (_tile[i].linePos)
		{
		case DRAW_LINE_POSITION::TOP:
			
			if (curr == 0)
			{
				_currentIndex = i;
				curr++;
			}

			if (_tile[i + 1].linePos == DRAW_LINE_POSITION::TOP) continue;
			else
			{
				_collisions.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.left,_tile[_currentIndex].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.top)),LINEAR_VALUE_TYPE::DOWN });
				curr = 0;

			}

			break;
		case DRAW_LINE_POSITION::BOTTOM:
			
			if (curr == 0)
			{
				_currentIndex = i;
				curr++;
			}

			if (_tile[i + 1].linePos == DRAW_LINE_POSITION::BOTTOM) continue;
			else
			{
				_collisions.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.left,_tile[_currentIndex].rc.bottom),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::UP });
				curr = 0;

			}

			
			break;
		case DRAW_LINE_POSITION::LEFT:
			
			if (curr == 0)
			{
				_currentIndex = i;
				curr++;
			}

			if (_tile[i + TILEX+1].linePos == DRAW_LINE_POSITION::LEFT) continue;
			else
			{
				_collisions.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.left,_tile[_currentIndex].rc.top),Vector2(_tile[i].rc.left,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::RIGHT });
				curr = 0;

			}

			
			break;
			case DRAW_LINE_POSITION::RIGHT:
			
			if (curr == 0)
			{
				_currentIndex = i;
				curr++;
			}

			if (_tile[i + TILEX+1].linePos == DRAW_LINE_POSITION::RIGHT) continue;
			else
			{
				_collisions.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.right,_tile[_currentIndex].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::LEFT });
				curr = 0;

			}

			
				break;
			default: 
				_currentIndex = 0;
				curr = 0;
				break;
		}


		
		
		
		
		
	}



}

void TestStage::release()
{
	Stage::release();
}

void TestStage::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void TestStage::render()
{
	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		_tileImage->setScale(2);
		_tileImage->frameRender(_tile[i].rc.getCenter(), _tile[i].tileFrameX, _tile[i].tileFrameY);
	}

	for (int i = 0; i < _collisions.size(); i++)
	{
		D2D_RENDERER->drawLine(_collisions[i].func.getStart(), _collisions[i].func.getEnd());
	}

	Stage::render();

}

void TestStage::mapLoad()
{
	HANDLE stageFile;
	DWORD read;

	stageFile = CreateFile("stage4.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(stageFile, _tile, sizeof(tagTileMap) * TILEX * TILEY, &read, NULL);

	CloseHandle(stageFile);
}
