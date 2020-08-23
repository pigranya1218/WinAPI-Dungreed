#include "StageManager.h"
#include "Stage.h"
#include "Player.h"
#include "UIManager.h"

void Stage::init()
{
	_state = STAGE_STATE::IDLE;

	_objectMgr = new ObjectManager;
	_objectMgr->setStage(this);
	_objectMgr->setPlayer(_player);

	_npcMgr = new NpcManager;
	_npcMgr->setStage(this);
	_npcMgr->setUIManager(_uiManager);
	_npcMgr->setObjectManager(_objectMgr);

	_enemyMgr = new EnemyManager;
	_enemyMgr->setStage(this);
	
	_projectileMgr = new ProjectileManager;
	_projectileMgr->setStage(this);
	_projectileMgr->setEnemyManager(_enemyMgr);
	_projectileMgr->setObjectManager(_objectMgr);

	_respawnPosition.resize(5);
	_doors.resize(4);

	_isGoNextStage = false;
}

void Stage::enter(int enterType)
{
	_uiManager->setMiniMap(_collisionGroundRects, _collisionGroundLines, _collisionPlatforms, _doors, _enemyMgr, _npcMgr, _objectMgr);
	if (enterType < 4) // 좌상우하 문으로 들어온 경우
	{
		_stageManager->setPlayerPos(_respawnPosition[enterType].x, _respawnPosition[enterType].y);
	}
	else // WORM으로 들어온 경우
	{
		Vector2 gate = _npcMgr->getGatePos();
		_stageManager->setPlayerPos(gate.x, gate.y + 10);
	}
	_isVisited = true;
	_stageManager->setShowPlayer(true);

	int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;
	CAMERA->setConfig(0, 0, WINSIZEX, WINSIZEY, 0, 0, stageWidth - WINSIZEX, stageHeight - WINSIZEY);
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

	int stageWidth = _tile[0].tileX * TILESIZE;
	int stageHeight = _tile[0].tileY * TILESIZE;
	Vector2 playerPos = _stageManager->getPlayerPos();

	CAMERA->setXY(Vector2(round(playerPos.x), round(playerPos.y)));

	switch (_state)
	{
	case STAGE_STATE::IDLE:
	{
		if (_spawnEnemies.size() > 0)
		{
			_state = STAGE_STATE::START;
			_spawnDelay = 0;
			_spawnIndex = 0;
			_spawnPhase = 1;
		}
		else
		{
			_state = STAGE_STATE::FINISH;
		}
	}
	break;
	case STAGE_STATE::START:
	{
		for (int i = 0; i < 4; i++)
		{
			if (_doors[i] != nullptr)
			{
				_doors[i]->setOpen(false);
			}
		}

		_spawnDelay -= elaspedTime;
		if (_spawnDelay <= 0)
		{
			_spawnDelay = 1;
			if (_spawnIndex < _spawnEnemies.size())
			{
				if (_spawnPhase == _spawnEnemies[_spawnIndex].phase)
				{
					_enemyMgr->spawnEnemy(_spawnEnemies[_spawnIndex].type, _spawnEnemies[_spawnIndex].pos, true);
					_spawnIndex++;
				}
				else
				{
					if (_enemyMgr->getEnemyCount() == 0)
					{
						_spawnPhase++;
					}
				}
			}
		}
		if (_spawnIndex >= _spawnEnemies.size() && _enemyMgr->getEnemyCount() == 0)
		{
			_state = STAGE_STATE::FINISH;
			if (_spawnChest.spawn)
			{
				_npcMgr->spawnNpc(_spawnChest.type, _spawnChest.pos, DIRECTION::LEFT);
			}
		}
	}
	break;
	case STAGE_STATE::FINISH:
	{
		for (int i = 0; i < 4; i++)
		{
			if (_doors[i] != nullptr)
			{
				_doors[i]->setOpen(true);
			}
		}
	}
	break;
	}

	if (KEY_MANAGER->isOnceKeyDown('L'))
	{
		for (int i = 0; i < 4; i++)
		{
			if (_doors[i] != nullptr)
			{
				_doors[i]->setOpen(!_doors[i]->isOpen());
			}
		}
	}

	if (_isGoNextStage)
	{
		_stageManager->nextStage();
	}
}

void Stage::render()
{
	D2D_RENDERER->fillRectangle(FloatRect(0, 0, TILESIZE * 30, TILESIZE * 20), 51, 49, 67, 1);
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

	/*for (int i = 0; i < _collisionGroundRects.size(); i++)
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
	}*/

	_npcMgr->render();
	_enemyMgr->render();
	_objectMgr->render();
	_projectileMgr->render();
}

void Stage::loadMap(string mapName)
{
	HANDLE stageFile;
	DWORD read;

	stageFile = CreateFile(mapName.c_str(), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


	ReadFile(stageFile, _tile, sizeof(tagTileMap) * MAXTILEX*MAXTILEY, &read, NULL);

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

	makeDoorAuto();

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
	case DRAW_LINE_POSITION::BLOCK:
	{
		if ((currX < maxSizeX - 1) && (_tile[currIndex + 1].linePos == DRAW_LINE_POSITION::BLOCK) && (startY == currY) && !isVisited[currX + 1][currY]) // 아직 세로 확장을 안했을 때만
		{
			makeMapToLine(startX, startY, currX + 1, currY, isVisited);
		}
		else // 세로로 확장할 수 있는지 검사하기
		{
			bool canAppendDown = true;
			if (currY >= maxSizeY - 1) // 세로 확장 불가능한 경우
			{
				canAppendDown = false;
			}
			else
			{
				for (int x = startX; x <= currX; x++)
				{
					if (_tile[x + maxSizeX * (currY + 1)].linePos != DRAW_LINE_POSITION::BLOCK)
					{
						canAppendDown = false;
						break;
					}
				}
			}
			
			if (canAppendDown) // 아래로 확장할 수 있는 경우
			{
				for (int x = startX; x < currX; x++)
				{
					isVisited[x][currY + 1] = true;
				}
				makeMapToLine(startX, startY, currX, currY + 1, isVisited);
			}
			else // 확장이 끝나서 충돌 렉트를 만듦
			{
				_collisionGroundRects.push_back(FloatRect(_tile[startIndex].rc.left, _tile[startIndex].rc.top, _tile[currIndex].rc.right, _tile[currIndex].rc.bottom));
			}
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
			_collisionGroundLines.push_back(LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.right, _tile[startIndex].rc.top - 2), Vector2(_tile[currIndex].rc.left, _tile[currIndex].rc.bottom - 2),
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
			_collisionGroundLines.push_back(LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top - 2), Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.bottom - 2),
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
			_collisionPlatforms.push_back(LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.right, _tile[startIndex].rc.top - 2), Vector2(_tile[currIndex].rc.left, _tile[currIndex].rc.bottom - 2),
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
			_collisionPlatforms.push_back(LinearFunc::getLinearFuncFromPoints(Vector2(_tile[startIndex].rc.left, _tile[startIndex].rc.top - 2), Vector2(_tile[currIndex].rc.right, _tile[currIndex].rc.bottom - 2),
				Vector2(_tile[startIndex].rc.left, _tile[currIndex].rc.right), Vector2(_tile[startIndex].rc.top, _tile[currIndex].rc.bottom)));
		}
	}
	break;
	}
}

void Stage::moveTo(GameObject* object, Vector2 const moveDir, bool checkCollisionGround, bool checkCollisionPlatform)
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
					if (checkCollisionPlatform)
					{
						newRc.bottom = _collisionPlatforms[i].b;
						newRc.top = newRc.bottom - object->getSize().y;
					}
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
							if (checkCollisionPlatform)
							{
								newRc.bottom = _collisionPlatforms[i].getY(newRc.left);
								newRc.top = newRc.bottom - object->getSize().y;
							}
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
							if (checkCollisionPlatform)
							{
								newRc.bottom = _collisionPlatforms[i].getY(newRc.right);
								newRc.top = newRc.bottom - object->getSize().y;
							}
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
		if (checkCollisionGround)
		{
			if (_collisionGroundRects[i].intersectEffect(newRc))
			{
				if (newRc.bottom == _collisionGroundRects[i].top)
				{
					object->setIsStand(true);
				}
			}
		}
	}

	// 문 사각형 검사
	for (int i = 0; i < 4; i++)
	{
		if (_doors[i] != nullptr)
		{
			if (!_doors[i]->isOpen())
			{
				FloatRect doorRect = FloatRect(_doors[i]->getPosition(), _doors[i]->getSize(), PIVOT::CENTER);
				if (doorRect.intersectEffect(newRc))
				{
					if (newRc.bottom == doorRect.top)
					{
						object->setIsStand(true);
					}
				}
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
					if (checkCollisionGround)
					{
						newRc.bottom = _collisionGroundLines[i].getY(newRc.left);
						newRc.top = newRc.bottom - object->getSize().y;
					}
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
					if (checkCollisionGround)
					{
						newRc.bottom = _collisionGroundLines[i].getY(newRc.right);
						newRc.top = newRc.bottom - object->getSize().y;
					}
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

void Stage::attack(FloatRect * rc, AttackInfo * info)
{
	_stageManager->attack(rc, info);
}

void Stage::attack(FloatCircle * circle, AttackInfo * info)
{
	_stageManager->attack(circle, info);
}

bool Stage::isHitEnemy(FloatRect* rc, AttackInfo* info)
{
	return (_enemyMgr->isHit(rc, info) || _objectMgr->isHit(rc, info));
}

bool Stage::isHitEnemy(FloatCircle* circle, AttackInfo* info)
{
	return (_enemyMgr->isHit(circle, info) || _objectMgr->isHit(circle, info));
}

bool Stage::isHitPlayer(Projectile * projectile, bool isOnceCollision)
{
	return _player->isHit(projectile, isOnceCollision);
}

Vector2 Stage::getPlayerPos()
{
	return _stageManager->getPlayerPos();
}

Vector2 Stage::getEnemyPos(const Vector2 & pos)
{
	return _enemyMgr->getEnemyPos(pos);
}

vector<FloatRect> Stage::getEnemyRects()
{
	return _enemyMgr->getEnemyRects();
}

void Stage::showDamage(DamageInfo info, Vector2 pos)
{
	_stageManager->showDamage(info, pos);
}

void Stage::showEnemyHp(float maxHp, float curHp, Vector2 pos)
{
	_stageManager->showEnemyHp(maxHp, curHp, pos);
}

void Stage::makeDoor(Vector2 pos, DIRECTION direction)
{
	DoorObject* door = new DoorObject;
	door->setObjectManager(_objectMgr);
	door->init(pos, direction);
	_objectMgr->pushObject(door);
	_doors[static_cast<int>(direction)] = door;
}

void Stage::makeDoorAuto()
{
	int maxSizeX = _tile[0].tileX;
	int maxSizeY = _tile[0].tileY;
	
	// UP CASE
	int count = 0;
	bool isMake = false;
	for (int y = 0; y <= 0 && !isMake; y++)
	{
		for (int x = 0; x <= maxSizeX; x++)
		{
			int index = y * maxSizeX + x;
			if (_tile[index].linePos == DRAW_LINE_POSITION::NOLINE)
			{
				count++;
			}
			else
			{
				if (count == 4)
				{
					int centerIndex = index - 2;
					makeDoor(Vector2(_tile[centerIndex].rc.left, _tile[centerIndex].rc.getCenter().y), DIRECTION::UP);
					_respawnPosition[1] = Vector2(_tile[centerIndex].rc.getCenter().x, _tile[centerIndex].rc.getCenter().y + 100);
					isMake = true;
					break;
				}
				count = 0;
			}
		}
		count = 0;
	}

	// DOWN CASE
	count = 0;
	isMake = false; 
	for (int y = maxSizeY - 1; y >= maxSizeY - 1 && !isMake; y--)
	{
		for (int x = 0; x <= maxSizeX; x++)
		{
			int index = y * maxSizeX + x;
			if (_tile[index].linePos == DRAW_LINE_POSITION::NOLINE)
			{
				count++;
			}
			else
			{
				if (count == 4)
				{
					int centerIndex = index - 2;
					makeDoor(Vector2(_tile[centerIndex].rc.left, _tile[centerIndex].rc.getCenter().y), DIRECTION::DOWN);
					_respawnPosition[3] = Vector2(_tile[centerIndex].rc.getCenter().x, _tile[centerIndex].rc.getCenter().y - 100);
					isMake = true;
					break;
				}
				count = 0;
			}
		}
		count = 0;
	}

	// LEFT CASE
	count = 0;
	isMake = false; 
	for (int x = 0; x <= 0 && !isMake; x++)
	{
		for (int y = 0; y <= maxSizeY; y++)
		{
			int index = y * maxSizeX + x;
			if (_tile[index].linePos == DRAW_LINE_POSITION::NOLINE)
			{
				count++;
			}
			else
			{
				if (count == 4)
				{
					int centerIndex = index - 2 * maxSizeX;
					makeDoor(Vector2(_tile[centerIndex].rc.getCenter().x, _tile[centerIndex].rc.top), DIRECTION::LEFT);
					_respawnPosition[0] = Vector2(_tile[centerIndex].rc.getCenter().x + 100, _tile[index].rc.top - 30);
					isMake = true;
					break;
				}
				count = 0;
			}
		}
		count = 0;
	}

	// RIGHT CASE
	count = 0;
	isMake = false; 
	for (int x = maxSizeX - 1; x >= maxSizeX - 1 && !isMake; x--)
	{
		for (int y = 0; y <= maxSizeY; y++)
		{
			int index = y * maxSizeX + x;
			if (_tile[index].linePos == DRAW_LINE_POSITION::NOLINE)
			{
				count++;
			}
			else
			{
				if (count == 4)
				{
					int centerIndex = index - 2 * maxSizeX;
					makeDoor(Vector2(_tile[centerIndex].rc.getCenter().x, _tile[centerIndex].rc.top), DIRECTION::RIGHT);
					_respawnPosition[2] = Vector2(_tile[centerIndex].rc.getCenter().x - 100, _tile[index].rc.top - 30);
					isMake = true;
					break;
				}
				count = 0;
			}
		}
		count = 0;
	}
}

vector<tagShowNpc> Stage::getNpcInfos()
{
	return _npcMgr->getNpcInfos();
}

void Stage::moveToIndex(Vector2 index)
{
	_stageManager->moveRoomIndex(index);
}

void Stage::nextStage()
{
	_isGoNextStage = true;
}

void Stage::setShowPlayer(bool showPlayer)
{
	_stageManager->setShowPlayer(showPlayer);
}

void Stage::activeBossUI(bool active)
{
	_uiManager->showBossHP(active);
}

void Stage::setBossUIHp(int maxHp, int currHp)
{
	_uiManager->setBossHP(maxHp, currHp);
}

void Stage::makeR2REvent(COLORREF color, float time)
{
	_stageManager->makeR2REvent(color, time);
}

void Stage::makeTimeRatioEvent(float ratio, float time)
{
	_stageManager->makeTimeRatioEvent(ratio, time);

}
