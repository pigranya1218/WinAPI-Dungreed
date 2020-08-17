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
	for (int i = 0; i < _tile[0].tileX * _tile[0].tileY; ++i)
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

	for (int i = 0; i < _collisionGroundRects.size(); i++)
	{
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_collisionGroundRects[i]), D2D1::ColorF::Enum::Red, 1, 1);
	}

	for (int i = 0; i < _collisionGroundLines.size(); i++)
	{
		D2D_RENDERER->drawLine(CAMERA->getRelativeV2(_collisionGroundLines[i].getStart()), CAMERA->getRelativeV2(_collisionGroundLines[i].getEnd()), D2D1::ColorF::Enum::Red, 1);
	}

	for (int i = 0; i < _collisionPlatforms.size(); i++)
	{
		D2D_RENDERER->drawLine(CAMERA->getRelativeV2(_collisionPlatforms[i].getStart()), CAMERA->getRelativeV2(_collisionPlatforms[i].getEnd()), D2D1::ColorF::Enum::Blue, 1);
	}

	int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;
	CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, stageWidth - WINSIZEX, stageHeight - WINSIZEY);
	CAMERA->setXY(_stageManager->getPlayerPos());

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
		else
		{
			_collisionGroundRects.push_back(rectMakePivot(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top), Vector2(TILESIZE * (currX - startX + 1), TILESIZE), PIVOT::LEFT_TOP));
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
			_collisionGroundRects.push_back(rectMakePivot(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top), Vector2(TILESIZE * (currX - startX + 1), TILESIZE), PIVOT::LEFT_TOP));
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
			_collisionGroundRects.push_back(rectMakePivot(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top), Vector2(TILESIZE, TILESIZE * (currY - startY + 1)), PIVOT::LEFT_TOP));
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
			_collisionGroundRects.push_back(rectMakePivot(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top), Vector2(TILESIZE, TILESIZE * (currY - startY + 1)), PIVOT::LEFT_TOP));
		}
	}
	break;
	case DRAW_LINE_POSITION::LEFT_TOP:
	{
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
			_collisionGroundRects.push_back(rectMakePivot(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top), Vector2(TILESIZE * (currX - startX + 1), TILESIZE), PIVOT::LEFT_TOP));
		}
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
			_collisionGroundRects.push_back(rectMakePivot(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top), Vector2(TILESIZE, TILESIZE * (currY - startY + 1)), PIVOT::LEFT_TOP));
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
			_collisionGroundRects.push_back(rectMakePivot(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top), Vector2(TILESIZE, TILESIZE * (currY - startY + 1)), PIVOT::LEFT_TOP));
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
			_collisionGroundRects.push_back(rectMakePivot(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top), Vector2(TILESIZE * (currX - startX + 1), TILESIZE), PIVOT::LEFT_TOP));
		}
	}
	break;
	case DRAW_LINE_POSITION::RIGHT_TOP:
	{
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
			_collisionGroundRects.push_back(rectMakePivot(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top), Vector2(TILESIZE * (currX - startX + 1), TILESIZE), PIVOT::LEFT_TOP));
		}
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
			_collisionGroundRects.push_back(rectMakePivot(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top), Vector2(TILESIZE, TILESIZE * (currY - startY + 1)), PIVOT::LEFT_TOP));
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
			_collisionGroundRects.push_back(rectMakePivot(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top), Vector2(TILESIZE, TILESIZE* (currY - startY + 1)), PIVOT::LEFT_TOP));
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
			_collisionGroundRects.push_back(rectMakePivot(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top), Vector2(TILESIZE * (currX - startX + 1), TILESIZE), PIVOT::LEFT_TOP));
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
			_collisionGroundLines.push_back(LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.right, _tile[startIndex].rc.top - 1), Vector2(_tile[currIndex].rc.left, _tile[currIndex].rc.bottom - 1),
				Vector2(_tile[currIndex].rc.left, _tile[startIndex].rc.right), Vector2(_tile[startIndex].rc.top, _tile[currIndex].rc.bottom)));
		}
	}
	break;
	case DRAW_LINE_POSITION::RIGHT_DIAGONAL:
	{
		if (currY < maxSizeY - 1 && currX < maxSizeX - 1 && _tile[currIndex + maxSizeX + 1].linePos == DRAW_LINE_POSITION::RIGHT_DIAGONAL)
		{
			makeMapToLine(startX, startY, currX + 1, currY + 1, isVisited);
		}
		else
		{
			_collisionGroundLines.push_back(LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top - 1), Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.bottom - 1),
				Vector2(_tile[startIndex].rc.left, _tile[currIndex].rc.right), Vector2(_tile[startIndex].rc.top, _tile[currIndex].rc.bottom)));
		}
	}
	break;
	case DRAW_LINE_POSITION::PLATFORM_TOP:
	{
		if (currX < maxSizeX - 1 && _tile[currIndex + 1].linePos == DRAW_LINE_POSITION::PLATFORM_TOP)
		{
			makeMapToLine(startX, startY, currX + 1, currY, isVisited);
		}
		else // 선분 종료 
		{
			_collisionPlatforms.push_back(LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top),Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.top),
				Vector2(_tile[startIndex].rc.left, _tile[currIndex].rc.right), Vector2(_tile[startIndex].rc.top, static_cast<float>(maxSizeY * TILESIZE))));
		}
	}
	break;
	case DRAW_LINE_POSITION::PLATFORM_LEFT_DIAGONAL:
	{
		if (currY < maxSizeY - 1 && currX > 0 && _tile[currIndex + maxSizeX - 1].linePos == DRAW_LINE_POSITION::PLATFORM_LEFT_DIAGONAL)
		{
			makeMapToLine(startX, startY, currX - 1, currY + 1, isVisited);
		}
		else
		{
			_collisionPlatforms.push_back(LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.right, _tile[startIndex].rc.top - 1), Vector2(_tile[currIndex].rc.left, _tile[currIndex].rc.bottom - 1),
				Vector2(_tile[currIndex].rc.left, _tile[startIndex].rc.right), Vector2(_tile[startIndex].rc.top, _tile[currIndex].rc.bottom)));
		}
	}
	break;
	case DRAW_LINE_POSITION::PLATFORM_RIGHT_DIAGONAL:
	{
		if (currY < maxSizeY - 1 && currX < maxSizeX - 1 && _tile[currIndex + maxSizeX + 1].linePos == DRAW_LINE_POSITION::PLATFORM_RIGHT_DIAGONAL)
		{
			makeMapToLine(startX, startY, currX + 1, currY + 1, isVisited);
		}
		else
		{
			_collisionPlatforms.push_back(LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top - 1), Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.bottom - 1),
				Vector2(_tile[startIndex].rc.left, _tile[currIndex].rc.right), Vector2(_tile[startIndex].rc.top, _tile[currIndex].rc.bottom)));
		}
	}
	break;
	}
}

void Stage::moveTo(GameObject* object, Vector2 const moveDir)
{
	object->setIsStand(false);
	FloatRect lastRc = FloatRect(object->getPosition(), object->getSize(), PIVOT::CENTER);
	FloatRect newRc = FloatRect(object->getPosition() + moveDir, object->getSize(), PIVOT::CENTER);

	// 플랫폼 검사
	for (int i = 0; i < _collisionPlatforms.size(); i++)
	{
		if (_collisionPlatforms[i].rangeX.x <= newRc.right && newRc.left <= _collisionPlatforms[i].rangeX.y) // 범위 안에 있을 때
		{
			// 이전까지는 발판 위에 있다가, 이번 업데이트에서 발판 아래로 내려간다면 발판에 올라타게 한다
			if (_collisionPlatforms[i].a == 0)
			{
				if (lastRc.bottom <= _collisionPlatforms[i].b && newRc.bottom > _collisionPlatforms[i].b)
				{
					newRc.bottom = _collisionPlatforms[i].b;
					newRc.top = newRc.bottom - object->getSize().y;
					object->setIsStand(true); // 땅에 서있는 경우
				}
			}
			else
			{
				if (_collisionPlatforms[i].a > 0) // 왼쪽 꼭지점을 기준으로 함
				{
					if (_collisionPlatforms[i].rangeX.x <= newRc.left && newRc.left <= _collisionPlatforms[i].rangeX.y) // 범위 안에 있을 때
					{
						if (_collisionPlatforms[i].getValueType(lastRc.left, lastRc.bottom) != LINEAR_VALUE_TYPE::DOWN
							&& _collisionPlatforms[i].getValueType(newRc.left, newRc.bottom) == LINEAR_VALUE_TYPE::DOWN)
						{
							newRc.bottom = _collisionPlatforms[i].getY(newRc.left);
							newRc.top = newRc.bottom - object->getSize().y;
							object->setIsStand(true);
						}
					}
				}
				else // 오른쪽 꼭지점을 기준으로 함
				{
					if (_collisionPlatforms[i].rangeX.x <= newRc.right && newRc.right <= _collisionPlatforms[i].rangeX.y) // 범위 안에 있을 때
					{
						if (_collisionPlatforms[i].getValueType(lastRc.right, lastRc.bottom) != LINEAR_VALUE_TYPE::DOWN
							&& _collisionPlatforms[i].getValueType(newRc.right, newRc.bottom) == LINEAR_VALUE_TYPE::DOWN)
						{
							newRc.bottom = _collisionPlatforms[i].getY(newRc.right);
							newRc.top = newRc.bottom - object->getSize().y;
							object->setIsStand(true);
						}
					}
				}
			}
		}
	}
	

	// 땅 사각형 검사
	for (int i = 0; i < _collisionGroundRects.size(); i++)
	{
		if (_collisionGroundRects[i].intersectEffect(newRc))
		{
			if (newRc.bottom == _collisionGroundRects[i].top)
			{
				object->setIsStand(true);
			}
		}
	}

	// 땅 대각 선분 검사
	for (int i = 0; i < _collisionGroundLines.size(); i++)
	{
		if (_collisionGroundLines[i].a > 0) // 왼쪽 꼭지점을 기준으로 함
		{
			if (_collisionGroundLines[i].rangeX.x <= newRc.left && newRc.left <= _collisionGroundLines[i].rangeX.y) // 범위 안에 있을 때
			{
				if (_collisionGroundLines[i].getValueType(newRc.left, newRc.bottom) == LINEAR_VALUE_TYPE::DOWN)
				{
					newRc.bottom = _collisionGroundLines[i].getY(newRc.left);
					newRc.top = newRc.bottom - object->getSize().y;
					object->setIsStand(true);
				}
			}
		}
		else // 오른쪽 꼭지점을 기준으로 함
		{
			if (_collisionGroundLines[i].rangeX.x <= newRc.right && newRc.right <= _collisionGroundLines[i].rangeX.y) // 범위 안에 있을 때
			{
				if(_collisionGroundLines[i].getValueType(newRc.right, newRc.bottom) == LINEAR_VALUE_TYPE::DOWN)
				{
					newRc.bottom = _collisionGroundLines[i].getY(newRc.right);
					newRc.top = newRc.bottom - object->getSize().y;
					object->setIsStand(true);
				}
			}
		}
	}

	object->setPosition(newRc.getCenter());
}

void Stage::attack(Projectile* projectile, AttackInfo* info)
{
	projectile->setAttackInfo(info);
	_projectileMgr->addProjectile(projectile);
}

bool Stage::isHitEnemy(FloatRect* rc, AttackInfo* info)
{
	return _enemyMgr->isHit(rc, info);
}

bool Stage::isHitEnemy(FloatCircle* circle, AttackInfo* info)
{
	return _enemyMgr->isHit(circle, info);
}

Vector2 Stage::getPlayerPos()
{
	return _stageManager->getPlayerPos();
}

