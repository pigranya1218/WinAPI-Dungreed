#include "DebugStage.h"
#include "StageManager.h"

void DebugStage::init()
{
	Stage::init();
	/*
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(0, 800), Vector2(WINSIZEX, 800)), LINEAR_VALUE_TYPE::DOWN });
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(0, 100), Vector2(WINSIZEX, 100)), LINEAR_VALUE_TYPE::UP });
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(50, 100), Vector2(50, 800)), LINEAR_VALUE_TYPE::LEFT });
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(1550, 100), Vector2(1550, 800)), LINEAR_VALUE_TYPE::RIGHT });
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(1250, 800), Vector2(1400, 650)), LINEAR_VALUE_TYPE::DOWN });
	_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(1400, 650), Vector2(1550, 650)), LINEAR_VALUE_TYPE::DOWN });
	
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(200, 700), Vector2(300, 700)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(300, 700), Vector2(700, 300)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(700, 300), Vector2(1550, 300)), LINEAR_VALUE_TYPE::DOWN });
	_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(1100, 500), Vector2(1250, 500)), LINEAR_VALUE_TYPE::DOWN });
	*/


	// 에너미 테스트입니다.
	_enemyMgr->setStage(this);
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_RED, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_NORMAL, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_ICE, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_ICE, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BANSHEE, Vector2(WINSIZEX / 2 - 300, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_MAGICIAN_ICE, Vector2(WINSIZEX / 2 - 500, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_SMALL_BOW, Vector2(WINSIZEX / 2 - 600, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::MINOTAURS, Vector2(WINSIZEX / 2 - 500, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_ICE, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_GIANT_RED, Vector2(WINSIZEX / 2 + 200, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::BAT_GIANT_NORMAL, Vector2(WINSIZEX / 2 + 400, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_NORMAL, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::GHOST, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::OVIBOS, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::BANSHEE, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	//_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_BIG_ICE, Vector2(WINSIZEX / 2, WINSIZEY / 2));
	_enemyMgr->spawnEnemy(ENEMY_TYPE::SKEL_MAGICIAN_ICE, Vector2(WINSIZEX / 2 + 600, WINSIZEY / 2 + 200));

	_tileImage = IMAGE_MANAGER->findImage("sampleTile1");
	
	mapLoad();
	
	
}

void DebugStage::release()
{
	Stage::release();

}

void DebugStage::update(float const elapsedTime)
{
	int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;
	CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, stageWidth - WINSIZEX, stageHeight - WINSIZEY);

	Stage::update(elapsedTime);

	CAMERA->setXY(_stageManager->getPlayerPos());
}

void DebugStage::render()
{
	for (int i = 0; i < _tile[0].tileX* _tile[0].tileY; ++i)
	{
		if (_tile[i].tileFrameX[0] != -1)
		{
			_tileImage->setScale(4);
			CAMERA->frameRender(_tileImage, _tile[i].rc.getCenter(), _tile[i].tileFrameX[0], _tile[i].tileFrameY[0]);
		}
		if (_tile[i].tileFrameX[1] != -1)
		{
			_tileImage->setScale(4);
			CAMERA->frameRender(_tileImage, _tile[i].rc.getCenter(), _tile[i].tileFrameX[1], _tile[i].tileFrameY[1]);
		}
	}

	for (int i = 0; i < _collisionGrounds.size(); i++)
	{
		D2D_RENDERER->drawLine(CAMERA->getRelativeV2(_collisionGrounds[i].func.getStart()), CAMERA->getRelativeV2(_collisionGrounds[i].func.getEnd()), D2D1::ColorF::Enum::Red, 1);
	}

	for (int i = 0; i < _collisionPlatforms.size(); i++)
	{
		D2D_RENDERER->drawLine(CAMERA->getRelativeV2(_collisionPlatforms[i].func.getStart()), CAMERA->getRelativeV2(_collisionPlatforms[i].func.getEnd()), D2D1::ColorF::Enum::Blue, 1);
	}

	Stage::render();

	//CAMERA->frameRender(_tileImage, Vector2(800,400));
}

void DebugStage::mapLoad()
{
	HANDLE stageFile;
	DWORD read;

	stageFile = CreateFile("StartRoom1.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


	ReadFile(stageFile, _tile, sizeof(tagTileMap) *2000, &read, NULL);

	CloseHandle(stageFile);
	
	int curr = 0;    	

	for (int i = 0; i <_tile[0].tileX* _tile[0].tileY; ++i)
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
				_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.left,_tile[_currentIndex].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.top)),LINEAR_VALUE_TYPE::DOWN });
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
				_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.left,_tile[_currentIndex].rc.bottom),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::UP });
				curr = 0;
			}

			break;
		case DRAW_LINE_POSITION::LEFT:
			if (curr == 0)
			{
				_currentIndex = i;
				curr++;
			}

			if (_tile[i + _tile[0].tileX + 1].linePos == DRAW_LINE_POSITION::LEFT) continue;
			else
			{
				_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.left,_tile[_currentIndex].rc.top),Vector2(_tile[i].rc.left,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::RIGHT });
				curr = 0;

			}

			break;
		case DRAW_LINE_POSITION::RIGHT:
			if (curr == 0)
			{
				_currentIndex = i;
				curr++;
			}

			if (_tile[i + _tile[0].tileX + 1].linePos == DRAW_LINE_POSITION::RIGHT) continue;
			else
			{
				_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.right,_tile[_currentIndex].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::LEFT });
				curr = 0;

			}

			break;

		case DRAW_LINE_POSITION::LEFT_TOP:
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.top),Vector2(_tile[i].rc.left,_tile[i].rc.bottom)), LINEAR_VALUE_TYPE::RIGHT });
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.top)), LINEAR_VALUE_TYPE::DOWN });
			break;
		case DRAW_LINE_POSITION::LEFT_BOTTOM:
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.top),Vector2(_tile[i].rc.left,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::RIGHT });
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.bottom),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::UP });
			break;
		case DRAW_LINE_POSITION::RIGHT_TOP:
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.top)),LINEAR_VALUE_TYPE::DOWN });
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.right,_tile[i].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::LEFT });
			break;
		case DRAW_LINE_POSITION::RIGHT_BOTTOM:
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.right,_tile[i].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::LEFT });
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.bottom),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::UP });
			break;
		case DRAW_LINE_POSITION::LEFT_DIAGONAL:
			if (curr == 0)
			{
				_currentIndex = i;
				curr++;
			}

			if (_tile[i + _tile[0].tileX - 2].linePos == DRAW_LINE_POSITION::LEFT_DIAGONAL) continue;
			else
			{
				_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[i].rc.left,_tile[i].rc.bottom),Vector2(_tile[_currentIndex].rc.right,_tile[_currentIndex].rc.top)),LINEAR_VALUE_TYPE::DOWN });
				curr = 0;

			}

			break;
		case DRAW_LINE_POSITION::RIGHT_DIAGONAL:
			if (curr == 0)
			{
				_currentIndex = i;
				curr++;
			}

			if (_tile[i + _tile[0].tileX + 3].linePos == DRAW_LINE_POSITION::RIGHT_DIAGONAL) continue;
			else
			{
				_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.left,_tile[_currentIndex].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.bottom)),LINEAR_VALUE_TYPE::DOWN });
				curr = 0;

			}

			break;
		case DRAW_LINE_POSITION::PLATFORM:
			if (curr == 0)
			{
				_currentIndex = i;
				curr++;
			}

			if (_tile[i + 1].linePos == DRAW_LINE_POSITION::PLATFORM) continue;
			else
			{
				_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[_currentIndex].rc.left,_tile[_currentIndex].rc.top),Vector2(_tile[i].rc.right,_tile[i].rc.top)),LINEAR_VALUE_TYPE::DOWN });
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
