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

	mapLoad();
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
	_objectMgr->update(elaspedTime);
	_npcMgr->update(elaspedTime);
	_enemyMgr->update(elaspedTime);
	_projectileMgr->update(elaspedTime);
	
}

void Stage::render()
{
	for (int i = 0; i < _tile[0].tileX * _tile[0].tileY; ++i)
	{
		if (_tile[i].tileFrameX[0] != -1)
		{
			_stageImage->setScale(4);
			CAMERA->frameRender(_stageImage, _tile[i].rc.getCenter(), _tile[i].tileFrameX[0], _tile[i].tileFrameY[0]);
		}
		if (_tile[i].tileFrameX[1] != -1)
		{
			_stageImage->setScale(4);
			CAMERA->frameRender(_stageImage, _tile[i].rc.getCenter(), _tile[i].tileFrameX[1], _tile[i].tileFrameY[1]);
		}
	}
	/*for (int i = 0; i < _collisionGrounds.size(); i++)
	{
		D2D_RENDERER->drawLine(CAMERA->getRelativeV2(_collisionGrounds[i].func.getStart()), CAMERA->getRelativeV2(_collisionGrounds[i].func.getEnd()), D2D1::ColorF::Enum::Red, 1);
	}

	for (int i = 0; i < _collisionPlatforms.size(); i++)
	{
		D2D_RENDERER->drawLine(CAMERA->getRelativeV2(_collisionPlatforms[i].func.getStart()), CAMERA->getRelativeV2(_collisionPlatforms[i].func.getEnd()), D2D1::ColorF::Enum::Blue, 1);
	}*/

	int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;
	CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, stageWidth - WINSIZEX, stageHeight - WINSIZEY);
	CAMERA->setXY(_stageManager->getPlayerPos());

	_objectMgr->render();
	_npcMgr->render();
	_enemyMgr->render();
	_projectileMgr->render();
	
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
				if (_collisionPlatforms[i].func.start <= newPoints[j].x && newPoints[j].x <= _collisionPlatforms[i].func.end) // 범위 안에 있을 때
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
				if (_collisionGrounds[i].func.start <= newPoints[j].y && newPoints[j].y <= _collisionGrounds[i].func.end) // 범위 안에 있을 때
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
				if (_collisionGrounds[i].func.start <= newPoints[j].x && newPoints[j].x <= _collisionGrounds[i].func.end) // 범위 안에 있을 때
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

void Stage::mapLoad()
{
	HANDLE stageFile;
	DWORD read;

	switch (_stageManager->getCurrStageType())
	{
	case STAGE_TYPE::VILLAGE:
		_stageImage = IMAGE_MANAGER->findImage("sampleTile3");
		stageFile = CreateFile("Town.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(stageFile, _tile, sizeof(tagTileMap) * MAXTILEX * MAXTILEY, &read, NULL);

		CloseHandle(stageFile);
		break;
	case STAGE_TYPE::DUNGEON_NORMAL:
		_stageImage = IMAGE_MANAGER->findImage("sampleTile1");
		break;
	case STAGE_TYPE::DUNGEON_BOSS:
		_stageImage = IMAGE_MANAGER->findImage("sampleTile1");
		break;
	case STAGE_TYPE::TEST:
		_stageImage = IMAGE_MANAGER->findImage("sampleTile1");
		stageFile = CreateFile("StartRoom1.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(stageFile, _tile, sizeof(tagTileMap) * MAXTILEX * MAXTILEY, &read, NULL);

		CloseHandle(stageFile);
		break;

	}


	

	int curr = 0;

	for (int i = 0; i < _tile[0].tileX * _tile[0].tileY; ++i)
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
