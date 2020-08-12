
#include "DebugStage.h"

void DebugStage::init()
{
	Stage::init();
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(0, 800), Vector2(WINSIZEX, 800)), LINEAR_VALUE_TYPE::DOWN });
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(300, 800), Vector2(1550, -450)), LINEAR_VALUE_TYPE::DOWN });
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(0, 100), Vector2(WINSIZEX, 100)), LINEAR_VALUE_TYPE::UP });
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(50, 100), Vector2(50, 800)), LINEAR_VALUE_TYPE::LEFT });
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(1550, 100), Vector2(1550, 800)), LINEAR_VALUE_TYPE::RIGHT });


	// 에너미 테스트입니다.
	_enemyMgr->setStage(this);
	/*_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_RED, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_NORMAL, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_ICE, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_ICE, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BANSHEE, Vector2(WINSIZEX / 2 - 300, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_MAGICIAN_ICE, Vector2(WINSIZEX / 2 - 500, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(WINSIZEX / 2 - 600, WINSIZEY / 2));*/


	/*_tileImage = IMAGE_MANAGER->findImage("sampleTile");
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
			case DRAW_LINE_POSITION::LEFT_DIAGONAL:
				if (curr == 0)
				{
					_currentIndex = i;
					curr++;
				}

				if (_tile[i + TILEX - 2].linePos == DRAW_LINE_POSITION::LEFT_DIAGONAL) continue;
				else
				{
					_collisions.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.bottom),Vector2(_tile[_currentIndex].rc.right,_tile[_currentIndex].rc.top)),LINEAR_VALUE_TYPE::DOWN });
					curr = 0;

				}

				break;
			case DRAW_LINE_POSITION::RIGHT_DIAGONAL:
				if (curr == 0)
				{
					_currentIndex = i;
					curr++;
				}

				if (_tile[i + TILEX + 3].linePos == DRAW_LINE_POSITION::RIGHT_DIAGONAL) continue;
				else
				{
					_collisions.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.left,_tile[_currentIndex].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::DOWN });
					curr = 0;

				}

				break;
			default:
				_currentIndex = 0;
				curr = 0;
				break;
		}







	}*/

}

void DebugStage::release()
{
	Stage::release();

}

void DebugStage::update(float const elapsedTime)
{
	Stage::update(elapsedTime);

}

void DebugStage::render()
{
	/*for (int i = 0; i < tilex*tiley; ++i)
	{
		_tileimage->setscale(2);
		_tileimage->framerender(_tile[i].rc.getcenter(), _tile[i].tileframex, _tile[i].tileframey);
	}*/

	for (int i = 0; i < _collisionGrounds.size(); i++)
	{
		D2D_RENDERER->drawLine(_collisionGrounds[i].func.getStart(), _collisionGrounds[i].func.getEnd(), D2D1::ColorF::Enum::Red, 1);
	}

	Stage::render();
}

void DebugStage::mapLoad()
{
	HANDLE stageFile;
	DWORD read;

	stageFile = CreateFile("stage5.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(stageFile, _tile, sizeof(tagTileMap) * TILEX * TILEY, &read, NULL);

	CloseHandle(stageFile);
}
