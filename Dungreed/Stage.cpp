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
	vector<vector<bool>> isVisited(maxSizeX, vector<bool>(maxSizeY, false)); // bool[maxSizeX][maxSizeY] �迭, false�� �ʱ�ȭ�Ǿ�����

	for (int i = 0; i < maxSizeX * maxSizeY; ++i)
	{
		int indexX = i % maxSizeX;
		int indexY = i / maxSizeX;
		if (isVisited[indexX][indexY]) continue; // �̹� �湮�� Ÿ���� �н�
		makeMapToLine(indexX, indexY, indexX, indexY, isVisited); // ���� Ÿ���� �������� ���� ����� ����

		
	}
}

void Stage::makeMapToLine(int startX, int startY, int currX, int currY, vector<vector<bool>>& isVisited)
{
	isVisited[currX][currY] = true; // �湮������ �湮�ߴٰ� ǥ��

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
			_collisionGroundLines.push_back(LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.right, _tile[startIndex].rc.top), Vector2(_tile[currIndex].rc.left, _tile[currIndex].rc.bottom),
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
			_collisionGroundLines.push_back(LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top), Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.bottom),
				Vector2(_tile[startIndex].rc.left, _tile[currIndex].rc.right), Vector2(_tile[startIndex].rc.top, _tile[currIndex].rc.bottom)));
		}
	}
	break;
	case DRAW_LINE_POSITION::PLATFORM:
	{
		if (currX < maxSizeX - 1 && _tile[currIndex + 1].linePos == DRAW_LINE_POSITION::PLATFORM)
		{
			makeMapToLine(startX, startY, currX + 1, currY, isVisited);
		}
		else // ���� ���� 
		{
			int startIndex = startX + startY * maxSizeX;
			_collisionPlatforms.push_back(LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top),Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.top),
				Vector2(_tile[startIndex].rc.left, _tile[currIndex].rc.right), Vector2(_tile[startIndex].rc.top, static_cast<float>(maxSizeY * TILESIZE))));
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

	// �÷��� �˻�
	for (int i = 0; i < _collisionPlatforms.size(); i++)
	{
		if (_collisionPlatforms[i].rangeX.x <= newRc.right && newRc.left <= _collisionPlatforms[i].rangeX.y) // ���� �ȿ� ���� ��
		{
			// ���������� ���� ���� �ִٰ�, �̹� ������Ʈ���� ���� �Ʒ��� �������ٸ� ���ǿ� �ö�Ÿ�� �Ѵ�
			if (_collisionPlatforms[i].a == 0)
			{
				if (lastRc.bottom <= _collisionPlatforms[i].b && newRc.bottom > _collisionPlatforms[i].b)
				{
					newRc.bottom = _collisionPlatforms[i].b;
					newRc.top = newRc.bottom - object->getSize().y;
					object->setIsStand(true); // ���� ���ִ� ���
				}
			}
			else
			{

			}
		}
	}

	// �� �簢�� �˻�
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

	// �� ���� �˻�
	//for (int i = 0; i < _collisionGroundLines.size(); i++)
	//{
	//	for (int j = 0; j < 4; j++) // �� �������� �˻�
	//	{
	//		bool isCollision = false;
	//		if (_collisionGroundLines[i].func.a == LinearFunc::INF_A) // ������
	//		{
	//			if (_collisionGroundLines[i].func.rangeY.x <= newPoints[j].y && newPoints[j].y <= _collisionGroundLines[i].func.rangeY.y &&
	//				_collisionGroundLines[i].func.rangeX.x <= newPoints[j].x && newPoints[j].x <= _collisionGroundLines[i].func.rangeX.y) // ���� �ȿ� ���� ��
	//			{
	//				if (_collisionGroundLines[i].func.getValueType(newPoints[j].x, newPoints[j].y) == _collisionGroundLines[i].collision)
	//				{
	//					newPoints[j].x = _collisionGroundLines[i].func.b;
	//					isCollision = true;
	//				}
	//			}
	//		}
	//		else // �������� �ƴ� ���
	//		{
	//			if (_collisionGroundLines[i].func.rangeY.x <= newPoints[j].y && newPoints[j].y <= _collisionGroundLines[i].func.rangeY.y &&
	//				_collisionGroundLines[i].func.rangeX.x <= newPoints[j].x && newPoints[j].x <= _collisionGroundLines[i].func.rangeX.y) // ���� �ȿ� ���� ��
	//			{
	//				if (_collisionGroundLines[i].func.getValueType(newPoints[j].x, newPoints[j].y) == _collisionGroundLines[i].collision)
	//				{
	//					newPoints[j].y = _collisionGroundLines[i].func.getY(newPoints[j].x);
	//					isCollision = true;
	//					if (_collisionGroundLines[i].collision == LINEAR_VALUE_TYPE::DOWN)
	//					{
	//						object->setIsStand(true); // ���� ���ִ� ���
	//					}
	//				}
	//			}
	//		}
	//		if (isCollision)
	//		{
	//			newCenter = Vector2(newPoints[j].x - calculatePoint[j][0] * radiusX, newPoints[j].y - calculatePoint[j][1] * radiusY);
	//			for (int k = 0; k < 4; k++)
	//			{
	//				newPoints[k] = Vector2(newCenter.x + calculatePoint[k][0] * radiusX, newCenter.y + calculatePoint[k][1] * radiusY);
	//			}
	//		}
	//	}
	//}

	// object->setPosition(newCenter);

	object->setPosition(newRc.getCenter());
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
