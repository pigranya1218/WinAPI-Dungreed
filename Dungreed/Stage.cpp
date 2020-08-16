#include "StageManager.h"
#include "Stage.h"
#include "Player.h"

void Stage::init()
{
	_objectMgr = new ObjectManager;
	
	_npcMgr = new NpcManager;
	
	_enemyMgr = new EnemyManager;
	
	_projectileMgr = new ProjectileManager;
	_projectileMgr->setStage(this);
}

void Stage::release()
{
	_objectMgr->release();
	delete _objectMgr;
	_npcMgr->release();
	delete _npcMgr; 
	_enemyMgr->release();
	delete _enemyMgr; 
	_projectileMgr->release();
	delete _projectileMgr;
}

void Stage::update(float const elaspedTime)
{
	_projectileMgr->update(elaspedTime);
	_objectMgr->update(elaspedTime);
	_npcMgr->update(elaspedTime);
	_enemyMgr->update(elaspedTime);
	
}

void Stage::render()
{
	_objectMgr->render();
	_npcMgr->render();
	_enemyMgr->render();
	_projectileMgr->render();
	
}

void Stage::loadMap(string mapName)
{
	HANDLE stageFile;
	DWORD read;

	stageFile = CreateFile(mapName.c_str(), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


	ReadFile(stageFile, _tile, sizeof(tagTileMap) * 2000, &read, NULL);

	CloseHandle(stageFile);

	int curr = 0;
	int currentIndex;
	int maxSizeX = _tile[0].tileX;
	int maxSizeY = _tile[0].tileY;
	vector<vector<bool>> isVisited(maxSizeX, vector<bool>(maxSizeY, false)); // bool[maxSizeX][maxSizeY] 배열, false로 초기화되어있음

	for (int i = 0; i < maxSizeX * maxSizeY; ++i)
	{
		int indexX = i % maxSizeX;
		int indexY = i / maxSizeX;
		if (isVisited[indexX][indexY]) continue; // 이미 방문한 타일은 패스
		makeMapToLine(indexX, indexY, indexX, indexY, isVisited); // 현재 타일을 시작으로 선분 만들기 시작

		
	}
}

void Stage::makeMapToLine(int startX, int startY, int currX, int currY, vector<vector<bool>>& isVisited)
{
	isVisited[currX][currY] = true; // 방문했으니 방문했다고 표시

	int maxSizeX = _tile[0].tileX;
	int maxSizeY = _tile[0].tileY;
	int startIndex = startX + startY * maxSizeX;
	int currIndex = currX + currY * maxSizeX;
	
	switch (_tile[currIndex].linePos)
	{
	case DRAW_LINE_POSITION::TOP:
	{
		if (currX < maxSizeX - 1 && (_tile[currIndex + 1].linePos == DRAW_LINE_POSITION::TOP || _tile[currIndex + 1].linePos == DRAW_LINE_POSITION::LEFT_TOP || _tile[currIndex + 1].linePos == DRAW_LINE_POSITION::RIGHT_TOP))
		{
			makeMapToLine(startX, startY, currX + 1, currY, isVisited);
		}
		else // 선분 종료 
		{
			int startIndex = startX + startY * maxSizeX;
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top),Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.top),
				Vector2(_tile[startIndex].rc.left, _tile[currIndex].rc.right), Vector2(_tile[startIndex].rc.top, _tile[startIndex].rc.top + TILESIZE)), LINEAR_VALUE_TYPE::DOWN });
		}
	}
	break;
	case DRAW_LINE_POSITION::BOTTOM:
	{
		if (currX < maxSizeX - 1 && (_tile[currIndex + 1].linePos == DRAW_LINE_POSITION::BOTTOM || _tile[currIndex + 1].linePos == DRAW_LINE_POSITION::LEFT_BOTTOM || _tile[currIndex + 1].linePos == DRAW_LINE_POSITION::RIGHT_BOTTOM))
		{
			makeMapToLine(startX, startY, currX + 1, currY, isVisited);
		}
		else
		{
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.bottom),Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.bottom),
				Vector2(_tile[startIndex].rc.left, _tile[currIndex].rc.right), Vector2(_tile[startIndex].rc.bottom - TILESIZE, _tile[startIndex].rc.bottom)), LINEAR_VALUE_TYPE::UP });
		}
	}
	break;
	case DRAW_LINE_POSITION::LEFT:
	{
		if (currY < maxSizeY - 1 && (_tile[currIndex + maxSizeX].linePos == DRAW_LINE_POSITION::LEFT || _tile[currIndex + maxSizeX].linePos == DRAW_LINE_POSITION::LEFT_TOP || _tile[currIndex + maxSizeX].linePos == DRAW_LINE_POSITION::LEFT_BOTTOM))
		{
			makeMapToLine(startX, startY, currX, currY + 1, isVisited);
		}
		else
		{
			int startIndex = startX + startY * maxSizeX;
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top),Vector2(_tile[currIndex].rc.left, _tile[currIndex].rc.bottom),
				Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.left + TILESIZE), Vector2(_tile[startIndex].rc.top, _tile[currIndex].rc.bottom)), LINEAR_VALUE_TYPE::RIGHT });
		}
	}
	break;
	case DRAW_LINE_POSITION::RIGHT:
	{
		if (currY < maxSizeY - 1 && (_tile[currIndex + maxSizeX].linePos == DRAW_LINE_POSITION::RIGHT || _tile[currIndex + maxSizeX].linePos == DRAW_LINE_POSITION::RIGHT_TOP || _tile[currIndex + maxSizeX].linePos == DRAW_LINE_POSITION::RIGHT_BOTTOM))
		{
			makeMapToLine(startX, startY, currX, currY + 1, isVisited);
		}
		else
		{
			int startIndex = startX + startY * maxSizeX;
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.right, _tile[startIndex].rc.top),Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.bottom),
				Vector2(_tile[startIndex].rc.right - TILESIZE, _tile[startIndex].rc.right), Vector2(_tile[startIndex].rc.top, _tile[currIndex].rc.bottom)), LINEAR_VALUE_TYPE::LEFT });
		}
	}
	break;
	case DRAW_LINE_POSITION::LEFT_TOP:
	{
		if (currY < maxSizeY - 1 && _tile[currIndex + maxSizeX].linePos == DRAW_LINE_POSITION::LEFT)
		{
			if (_tile[startIndex].linePos == DRAW_LINE_POSITION::LEFT)
			{
				makeMapToLine(startX, startY, currX, currY + 1, isVisited);
			}
			else
			{
				makeMapToLine(currX, currY, currX, currY + 1, isVisited);
			}
		}
		else
		{
			int startIndex = startX + startY * maxSizeX;
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top),Vector2(_tile[currIndex].rc.left, _tile[currIndex].rc.bottom),
				Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.left + TILESIZE), Vector2(_tile[startIndex].rc.top, _tile[currIndex].rc.bottom)), LINEAR_VALUE_TYPE::RIGHT });
		}
		if (currX < maxSizeX - 1 && _tile[currIndex + 1].linePos == DRAW_LINE_POSITION::TOP)
		{
			if (_tile[startIndex].linePos == DRAW_LINE_POSITION::TOP)
			{
				makeMapToLine(startX, startY, currX + 1, currY, isVisited);
			}
			else
			{
				makeMapToLine(currX, currY, currX + 1, currY, isVisited);
			}
		}
		else
		{
			int startIndex = startX + startY * maxSizeX;
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top),Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.top),
				Vector2(_tile[startIndex].rc.left, _tile[currIndex].rc.right), Vector2(_tile[startIndex]. rc.top, _tile[startIndex].rc.top + TILESIZE)), LINEAR_VALUE_TYPE::DOWN });
		}
	}
	break;
	case DRAW_LINE_POSITION::LEFT_BOTTOM:
	{
		if (currY < maxSizeY - 1 && _tile[currIndex + maxSizeX].linePos == DRAW_LINE_POSITION::LEFT)
		{
			if (_tile[startIndex].linePos == DRAW_LINE_POSITION::LEFT)
			{
				makeMapToLine(startX, startY, currX, currY + 1, isVisited);
			}
			else
			{
				makeMapToLine(currX, currY, currX, currY + 1, isVisited);
			}
		}
		else
		{
			int startIndex = startX + startY * maxSizeX;
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top),Vector2(_tile[currIndex].rc.left, _tile[currIndex].rc.bottom),
				Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.left + TILESIZE), Vector2(_tile[startIndex].rc.top, _tile[currIndex].rc.bottom)), LINEAR_VALUE_TYPE::RIGHT });
		}
		if (currX < maxSizeX - 1 && _tile[currIndex + 1].linePos == DRAW_LINE_POSITION::BOTTOM)
		{
			if (_tile[startIndex].linePos == DRAW_LINE_POSITION::BOTTOM)
			{
				makeMapToLine(startX, startY, currX + 1, currY, isVisited);
			}
			else
			{
				makeMapToLine(currX, currY, currX + 1, currY, isVisited);
			}
		}
		else
		{
			int startIndex = startX + startY * maxSizeX;
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.bottom),Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.bottom),
				Vector2(_tile[startIndex].rc.left, _tile[currIndex].rc.right), Vector2(_tile[startIndex].rc.bottom - TILESIZE, _tile[startIndex].rc.bottom)), LINEAR_VALUE_TYPE::UP });
		}
	}
	break;
	case DRAW_LINE_POSITION::RIGHT_TOP:
	{
		if (currY < maxSizeY - 1 && _tile[currIndex + maxSizeX].linePos == DRAW_LINE_POSITION::RIGHT)
		{
			if (_tile[startIndex].linePos == DRAW_LINE_POSITION::RIGHT)
			{
				makeMapToLine(startX, startY, currX, currY + 1, isVisited);
			}
			else
			{
				makeMapToLine(currX, currY, currX, currY + 1, isVisited);
			}
		}
		else
		{
			int startIndex = startX + startY * maxSizeX;
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.right, _tile[startIndex].rc.top),Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.bottom),
				Vector2(_tile[startIndex].rc.right - TILESIZE, _tile[startIndex].rc.right), Vector2(_tile[startIndex].rc.top, _tile[currIndex].rc.bottom)), LINEAR_VALUE_TYPE::LEFT });
		}
		if (currX < maxSizeX - 1 && _tile[currIndex + 1].linePos == DRAW_LINE_POSITION::TOP)
		{
			if (_tile[startIndex].linePos == DRAW_LINE_POSITION::TOP)
			{
				makeMapToLine(startX, startY, currX + 1, currY, isVisited);
			}
			else
			{
				makeMapToLine(currX, currY, currX + 1, currY, isVisited);
			}
		}
		else
		{
			int startIndex = startX + startY * maxSizeX;
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top),Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.top),
				Vector2(_tile[startIndex].rc.left, _tile[currIndex].rc.right), Vector2(_tile[startIndex].rc.top, _tile[startIndex].rc.top - TILESIZE)), LINEAR_VALUE_TYPE::DOWN });
		}
	}
	break;
	case DRAW_LINE_POSITION::RIGHT_BOTTOM:
	{
		if (currY < maxSizeY - 1 && _tile[currIndex + maxSizeX].linePos == DRAW_LINE_POSITION::RIGHT)
		{
			if (_tile[startIndex].linePos == DRAW_LINE_POSITION::RIGHT)
			{
				makeMapToLine(startX, startY, currX, currY + 1, isVisited);
			}
			else
			{
				makeMapToLine(currX, currY, currX, currY + 1, isVisited);
			}
		}
		else
		{
			int startIndex = startX + startY * maxSizeX;
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.right, _tile[startIndex].rc.top),Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.bottom),
				Vector2(_tile[startIndex].rc.right - TILESIZE, _tile[startIndex].rc.right), Vector2(_tile[startIndex].rc.top, _tile[currIndex].rc.bottom)), LINEAR_VALUE_TYPE::LEFT });
		}
		if (currX < maxSizeX - 1 && _tile[currIndex + 1].linePos == DRAW_LINE_POSITION::BOTTOM)
		{
			if (_tile[startIndex].linePos == DRAW_LINE_POSITION::BOTTOM)
			{
				makeMapToLine(startX, startY, currX + 1, currY, isVisited);
			}
			else
			{
				makeMapToLine(currX, currY, currX + 1, currY, isVisited);
			}
		}
		else
		{
			int startIndex = startX + startY * maxSizeX;
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.bottom),Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.bottom),
				Vector2(_tile[startIndex].rc.left, _tile[currIndex].rc.right), Vector2(_tile[startIndex].rc.bottom - TILESIZE, _tile[startIndex].rc.bottom)), LINEAR_VALUE_TYPE::UP });
		}
	}
	break;
	case DRAW_LINE_POSITION::LEFT_DIAGONAL:
	{
		if (currY < maxSizeY - 1 && currX > 0 && _tile[currIndex + maxSizeX - 1].linePos == DRAW_LINE_POSITION::LEFT_DIAGONAL)
		{
			makeMapToLine(startX, startY, currX - 1, currY + 1, isVisited);
		}
		else
		{
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.right, _tile[startIndex].rc.top), Vector2(_tile[currIndex].rc.left, _tile[currIndex].rc.bottom),
				Vector2(_tile[currIndex].rc.left, _tile[startIndex].rc.right), Vector2(_tile[startIndex].rc.top, _tile[currIndex].rc.bottom)),LINEAR_VALUE_TYPE::DOWN });
		}
	}
	break;
	case DRAW_LINE_POSITION::RIGHT_DIAGONAL:
	{
		if (currY < maxSizeY - 1 && currX < maxSizeX - 1 && _tile[currIndex + maxSizeX + 1].linePos == DRAW_LINE_POSITION::RIGHT_DIAGONAL)
		{
			makeMapToLine(startX, startY, currX - 1, currY + 1, isVisited);
		}
		else
		{
			_collisionGrounds.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top), Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.bottom),
				Vector2(_tile[startIndex].rc.left, _tile[currIndex].rc.right), Vector2(_tile[startIndex].rc.top, _tile[currIndex].rc.bottom)),LINEAR_VALUE_TYPE::DOWN });
		}
	}
	break;
	case DRAW_LINE_POSITION::PLATFORM:
	{
		if (currX < maxSizeX - 1 && _tile[currIndex + 1].linePos == DRAW_LINE_POSITION::PLATFORM)
		{
			makeMapToLine(startX, startY, currX + 1, currY, isVisited);
		}
		else // 선분 종료 
		{
			int startIndex = startX + startY * maxSizeX;
			_collisionPlatforms.push_back({ LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top),Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.top),
				Vector2(_tile[startIndex].rc.left, _tile[currIndex].rc.right), Vector2(_tile[startIndex].rc.top, static_cast<float>(maxSizeY * TILESIZE))), LINEAR_VALUE_TYPE::DOWN });
		}
	}
	break;
	}
}

void Stage::moveTo(GameObject* object, Vector2 const moveDir)
{
	object->setIsStand(false);
	Vector2 lastCenter = object->getPosition();
	Vector2 newCenter = lastCenter + moveDir;
	float radiusX = object->getSize().x / 2;
	float radiusY = object->getSize().y / 2;
	int calculatePoint[4][2] = { {-1, -1}, {1, -1}, {1, 1}, {-1, 1}}; // 좌상, 우상, 우하, 좌하
	Vector2 lastPoints[4];
	Vector2 newPoints[4];
	for (int i = 0; i < 4; i++)
	{
		lastPoints[i] = Vector2(lastCenter.x + calculatePoint[i][0] * radiusX, lastCenter.y + calculatePoint[i][1] * radiusY);
		newPoints[i] = Vector2(newCenter.x + calculatePoint[i][0] * radiusX, newCenter.y + calculatePoint[i][1] * radiusY);
	}

	// 발판 검사
	for (int i = 0; i < _collisionPlatforms.size(); i++)
	{
		for (int j = 2; j <= 3; j++) // 아래 꼭짓점들만 검사
		{
			bool isCollision = false;
			if (_collisionPlatforms[i].func.a == LinearFunc::INF_A) // 수직선
			{
				// 발판이 수직선인 경우는 없음
			}
			else // 수직선이 아닌 경우
			{
				if (_collisionPlatforms[i].func.rangeX.x <= newPoints[j].x && newPoints[j].x <= _collisionPlatforms[i].func.rangeX.y) // 범위 안에 있을 때
				{
					// 이전까지는 발판 위에 있다가, 이번 업데이트에서 발판 아래로 내려간다면 발판에 올라타게 한다

					LINEAR_VALUE_TYPE leftFoot = _collisionPlatforms[i].func.getValueType(lastPoints[3].x, lastPoints[3].y);
					LINEAR_VALUE_TYPE rightFoot = _collisionPlatforms[i].func.getValueType(lastPoints[2].x, lastPoints[2].y);
					if ((leftFoot != _collisionPlatforms[i].collision) &&
						(rightFoot != _collisionPlatforms[i].collision) &&
						(_collisionPlatforms[i].func.getValueType(newPoints[j].x, newPoints[j].y) == _collisionPlatforms[i].collision))
					{
						newPoints[j].y = _collisionPlatforms[i].func.getY(newPoints[j].x);
						isCollision = true;
						if (_collisionPlatforms[i].collision == LINEAR_VALUE_TYPE::DOWN)
						{
							object->setIsStand(true); // 땅에 서있는 경우
						}
					}
				}
			}
			if (isCollision)
			{
				newCenter = Vector2(newPoints[j].x - calculatePoint[j][0] * radiusX, newPoints[j].y - calculatePoint[j][1] * radiusY);
				for (int k = 0; k < 4; k++)
				{
					newPoints[k] = Vector2(newCenter.x + calculatePoint[k][0] * radiusX, newCenter.y + calculatePoint[k][1] * radiusY);
				}
			}
		}
	}

	// 땅 검사
	for (int i = 0; i < _collisionGrounds.size(); i++)
	{
		for (int j = 0; j < 4; j++) // 각 꼭짓점별 검사
		{
			bool isCollision = false;
			if (_collisionGrounds[i].func.a == LinearFunc::INF_A) // 수직선
			{
				if (_collisionGrounds[i].func.rangeY.x <= newPoints[j].y && newPoints[j].y <= _collisionGrounds[i].func.rangeY.y &&
					_collisionGrounds[i].func.rangeX.x <= newPoints[j].x && newPoints[j].x <= _collisionGrounds[i].func.rangeX.y) // 범위 안에 있을 때
				{
					if (_collisionGrounds[i].func.getValueType(newPoints[j].x, newPoints[j].y) == _collisionGrounds[i].collision)
					{
						newPoints[j].x = _collisionGrounds[i].func.b;
						isCollision = true;
					}
				}
			}
			else // 수직선이 아닌 경우
			{
				if (_collisionGrounds[i].func.rangeY.x <= newPoints[j].y && newPoints[j].y <= _collisionGrounds[i].func.rangeY.y &&
					_collisionGrounds[i].func.rangeX.x <= newPoints[j].x && newPoints[j].x <= _collisionGrounds[i].func.rangeX.y) // 범위 안에 있을 때
				{
					if (_collisionGrounds[i].func.getValueType(newPoints[j].x, newPoints[j].y) == _collisionGrounds[i].collision)
					{
						newPoints[j].y = _collisionGrounds[i].func.getY(newPoints[j].x);
						isCollision = true;
						if (_collisionGrounds[i].collision == LINEAR_VALUE_TYPE::DOWN)
						{
							object->setIsStand(true); // 땅에 서있는 경우
						}
					}
				}
			}
			if (isCollision)
			{
				newCenter = Vector2(newPoints[j].x - calculatePoint[j][0] * radiusX, newPoints[j].y - calculatePoint[j][1] * radiusY);
				for (int k = 0; k < 4; k++)
				{
					newPoints[k] = Vector2(newCenter.x + calculatePoint[k][0] * radiusX, newCenter.y + calculatePoint[k][1] * radiusY);
				}
			}
		}
	}

	object->setPosition(newCenter);
}

void Stage::attack(FloatRect* rect, AttackInfo* info)
{
}

void Stage::attack(FloatCircle* circle, AttackInfo* info)
{
}

void Stage::attack(Projectile* projectile, AttackInfo* info)
{
	_projectileMgr->addProjectile(projectile);
}

Vector2 Stage::getPlayerPos()
{
	return _stageManager->getPlayerPos();
}
