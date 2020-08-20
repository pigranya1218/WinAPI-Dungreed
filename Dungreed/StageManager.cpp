#include "stdafx.h"
#include "StageManager.h"
#include "GameScene.h"
#include "Player.h"
#include "UIManager.h"

#include "DebugStage.h"
#include "VillageStage.h"

#include "AllRoom.h"


Stage * StageManager::getStage(int stageType, bool isWall[])
{
	
	switch (stageType)
	{
	case 0: // 일반 방
	{
		if (!isWall[0] && !isWall[1] && !isWall[2] && !isWall[3]) // 좌,상,우,하가 뚫린 경우
		{
			int rand = RANDOM->getInt(2);
			if(rand==0)resultRoom = new Room20LTRB;
			else if(rand==1)resultRoom = new Room22LTRB;
		}
		else if (!isWall[0] && !isWall[1] && !isWall[2] && isWall[3])//좌,상,우  뚫린 경우
		{
			int rand = RANDOM->getInt(2);
			resultRoom = new Room2LTR;
		}
		else if (!isWall[0] && isWall[1] && !isWall[2] && !isWall[3])//좌, 우, 하  뚫린 경우
		{
			resultRoom = new Room12LRB;
		}
		else if (!isWall[0] && isWall[1] && !isWall[2] && isWall[3])//좌, 우 뚫린 경우
		{
			int rand = RANDOM->getInt(3);
			if(rand==0)resultRoom = new Room21LR;
			else if(rand==1)resultRoom = new Room4LR;
			else if(rand==2)resultRoom = new Room5LR;
			else resultRoom = new Room21LR;
		}
		else if (isWall[0] && !isWall[1] && isWall[2] && !isWall[3])//상, 하 뚫린 경우
		{
			resultRoom = new Room6TB;
			//resultRoom = new room
		}
		else if (!isWall[0] && !isWall[1] && isWall[2] && isWall[3])//좌, 상 뚫린 경우
		{
			resultRoom = new Room11LT;
		}
		else if (!isWall[0] && isWall[1] && isWall[2] && !isWall[3])//좌, 하 뚫린 경우
		{
			resultRoom = new Room11_LB;
		}
		else if (isWall[0] && !isWall[1] && !isWall[2] && isWall[3])//상, 우 뚫린 경우
		{
			resultRoom = new Room7RT;
		}
		else if (!isWall[0] && isWall[1] && !isWall[2] && !isWall[3])//우, 하 뚫린 경우
		{
			resultRoom = new Room7_RB;
		}
		if (!isWall[0] && isWall[1] && isWall[2] && isWall[3])//좌 뚫린 경우
		{
			resultRoom = new Room8L;
		}
		else if (isWall[0] && isWall[1] && !isWall[2] && isWall[3])//우 뚫린 경우
		{
			resultRoom = new Room1R;
		}
		else if (isWall[0] && !isWall[1] && isWall[2] && isWall[3])//상 뚫린 경우
		{
			resultRoom = new Room10T;
		}
		else if (isWall[0] && isWall[1] && isWall[2] && !isWall[3])//하 뚫린 경우
		{
			resultRoom = new Room9B;
		}
	} 
	break;
	case 1: // 시작방
	{
		if (isWall[0] && isWall[1] && !isWall[2] && isWall[3]) // 우 뚫린 경우
		{
			resultRoom = new StartRoom1;
		}
		else if (isWall[0] && isWall[1] && !isWall[2] && !isWall[3]) //우, 하 꿇린 경우
		{
			resultRoom = new StartRoom2;

		}
	}
	break;
	case 2: // 끝방
	{
		if (!isWall[0] && isWall[1] && isWall[2] && isWall[3]) // 좌 뚫린 경우
		{
			resultRoom = new DownStair1L;
		}
		/*else if (isWall[0] && isWall[1] && !isWall[2] && !isWall[3]) 
		{
			

		}*/
	}
	break;
	case 3: // 식당방
	{
		if (!isWall[0] && isWall[1] && !isWall[2] && isWall) // 좌, 우가 뚫린 경우
		{
			resultRoom = new RestaurantRoom;
		}
		else if (!isWall[0] && isWall[1] && isWall[2] && isWall) // 좌가 뚫린 경우
		{
			resultRoom = new RestaurantRoom;
		}
	}
	break;
	case 4: // 상점방
	{
		if (!isWall[0] && isWall[1] && !isWall[2] && isWall) // 좌, 우가 뚫린 경우
		{
			resultRoom = new DungeonShopRoom;
		}
		else if (!isWall[0] && !isWall[1] && !isWall[2] && isWall) // 좌, 상, 우가 뚫린 경우
		{
			resultRoom = new DungeonShopRoom2;
		}
	}
	break;
	}

	resultRoom->init();
	resultRoom->setPlayer(_player);
	resultRoom->setStageManager(this);
	return resultRoom;
}

void StageManager::init()
{
	_currStageType = STAGE_TYPE::TEST;
	_mapSize = 4;
	makeStage();
}

void StageManager::release()
{
	
	releaseStage();
}

void StageManager::update(float const elapsedTime)
{
	_currStage->update(elapsedTime);
}

void StageManager::render()
{
	_currStage->render();
}

void StageManager::attack(FloatRect* rect, AttackInfo* info)
{
	if (info->team == OBJECT_TEAM::PLAYER)
	{
		_currStage->isHitEnemy(rect, info);
	}
	else
	{
		if (_player->isHit(rect, info))
		{
			_player->hitEffect(rect, info);
		}
	}
}

void StageManager::attack(FloatCircle* circle, AttackInfo* info)
{
	if (info->team == OBJECT_TEAM::PLAYER)
	{
		_currStage->isHitEnemy(circle, info);
	}
	else
	{
		if (_player->isHit(circle, info))
		{
			_player->hitEffect(circle, info);
		}
	}
}

void StageManager::attack(Projectile* projectile, AttackInfo* info)
{
	_currStage->attack(projectile, info);
}


void StageManager::moveTo(GameObject* object, Vector2 moveDir)
{
	_currStage->moveTo(object, moveDir);
}

void StageManager::nextStage()
{
	_currStageType = static_cast<STAGE_TYPE>(static_cast<int>(_currStageType) + 1);
	releaseStage();
	makeStage();
}

void StageManager::moveRoom(Vector2 moveDir)
{
	_currIndexX += moveDir.x;
	_currIndexY += moveDir.y;

	_currStage = _stageMap[_currIndexX][_currIndexY];
}

void StageManager::makeStage()
{
	releaseStage();
	_stageMap.resize(_mapSize);
	for (int i = 0; i < _mapSize; i++)
	{
		_stageMap[i].resize(_mapSize);
	}

	switch (_currStageType)
	{
	case STAGE_TYPE::VILLAGE:
		_currStage = new VillageStage();
		_currStage->setStageManager(this);
		_currStage->init();
		break;
	case STAGE_TYPE::DUNGEON_NORMAL:
		makeDungeon();
		break;
	case STAGE_TYPE::DUNGEON_BOSS:
		makeDungeon();
		break;
	case STAGE_TYPE::TEST:
		_currStage = new DebugStage();
		_currStage->setStageManager(this);
		_currStage->setUIManager(_uiMgr);
		_currStage->setPlayer(_player);
		_currStage->init();
		_currStage->enter();
		break;
	default:
		break;
	}
}

void StageManager::makeDungeon()
{
	_roomInfo.resize(_mapSize);
	for (int i = 0; i < _mapSize; i++)
	{
		_roomInfo[i].resize(_mapSize);
	}

	while (true)
	{
		// 맵 정보 초기화
		for (int x = 0; x < _mapSize; x++)
		{
			for (int y = 0; y < _mapSize; y++)
			{
				for (int dir = 0; dir < 4; dir++)
				{
					_roomInfo[x][y].isWall[dir] = true;
				}
				_roomInfo[x][y].isVisited = false;
			}
		}
		int startX = RANDOM->getInt(_mapSize);
		int startY = RANDOM->getInt(_mapSize);
		makeRoom(startX, startY);

		if (makeSpecialRoom()) // 시작방, 끝방, 식당방, 상점방을 만들 수 있는 맵이라면 멈춤
		{
			break;
		}
	}

	// 생성한 지도에 맞는 방 만들기
	for (int x = 0; x < _mapSize; x++)
	{
		for (int y = 0; y < _mapSize; y++)
		{
			if (_roomInfo[x][y].roomType == -1) continue;
			if (_roomInfo[x][y].roomType == 1)
			{
				_currIndexX = x;
				_currIndexY = y;
			}
			_stageMap[x][y] = getStage(_roomInfo[x][y].roomType, _roomInfo[x][y].isWall);
		}
	}
		
	_currStage = _stageMap[_currIndexX][_currIndexY];
}

void StageManager::makeRoom(int x, int y)
{
	if (_roomInfo[x][y].isVisited) return;

	int move[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} }; // L T R B
	bool checkDir[4] = { false, false, false, false };
	while(true)
	{
		if (checkDir[0] && checkDir[1] && checkDir[2] && checkDir[3]) break;

		int randomDir = RANDOM->getInt(4);
		if (checkDir[randomDir]) continue;
		checkDir[randomDir] = true;

		int newX = x + move[randomDir][0];
		int newY = y + move[randomDir][1];

		if (newX < 0 || newX >= _mapSize || newY < 0 || newY >= _mapSize) continue;
		if (_roomInfo[newX][newY].isVisited) continue;

		_roomInfo[x][y].isWall[randomDir] = false;
		_roomInfo[newX][newY].isWall[(randomDir + 2) % 4] = false;
		makeRoom(newX, newY);
	}
}

bool StageManager::makeSpecialRoom()
{
	// 시작점 만들기
	vector<Vector2> candidate;
	Vector2 start;
	Vector2 end;
	Vector2 restaurant;
	Vector2 shop;

	for (int x = 0; x < _mapSize; x++)
	{
		for (int y = 0; y < _mapSize; y++)
		{
			if (_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && !_roomInfo[x][y].isWall[2] && !_roomInfo[x][y].isWall[3]) // 우 하
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && !_roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // 우
			{
				candidate.push_back(Vector2(x, y));
			}
		}
	}

	if (candidate.size() == 0) return false;
	int random = RANDOM->getInt(candidate.size());
	start = candidate[random];
	_roomInfo[start.x][start.y].roomType = 1;

	// 끝점 만들기
	candidate.clear();
	for (int x = 0; x < _mapSize; x++)
	{
		for (int y = 0; y < _mapSize; y++)
		{
			if (start.x == x && start.y == y) continue;
			if (!_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && _roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // 좌
			{
				candidate.push_back(Vector2(x, y));
			}
		}
	}

	if (candidate.size() == 0) return false;
	random = RANDOM->getInt(candidate.size());
	end = candidate[random];
	_roomInfo[end.x][end.y].roomType = 2;

	// 식당 만들기
	candidate.clear();
	for (int x = 0; x < _mapSize; x++)
	{
		for (int y = 0; y < _mapSize; y++)
		{
			if (start.x == x && start.y == y) continue;
			if (end.x == x && end.y == y) continue;
			if (!_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && !_roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // 좌 우
			{
				candidate.push_back(Vector2(x, y));
			}
		}
	}

	if (candidate.size() == 0) return false;
	random = RANDOM->getInt(candidate.size());
	restaurant = candidate[random];
	_roomInfo[restaurant.x][restaurant.y].roomType = 3;

	// 상점 만들기
	candidate.clear();
	for (int x = 0; x < _mapSize; x++)
	{
		for (int y = 0; y < _mapSize; y++)
		{
			if (start.x == x && start.y == y) continue;
			if (end.x == x && end.y == y) continue;
			if (restaurant.x == x && restaurant.y == y) continue;
			if (!_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && !_roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // 좌 우
			{
				candidate.push_back(Vector2(x, y));
			}
		}
	}

	if (candidate.size() == 0) return false;
	random = RANDOM->getInt(candidate.size());
	shop = candidate[random];
	_roomInfo[shop.x][shop.y].roomType = 4;

	// 랜덤으로 끝방들 몇 개 지우기
	candidate.clear();
	for (int x = 0; x < _mapSize; x++)
	{
		for (int y = 0; y < _mapSize; y++)
		{
			if (start.x == x && start.y == y) continue;
			if (end.x == x && end.y == y) continue;
			if (restaurant.x == x && restaurant.y == y) continue;
			if (shop.x == x && shop.y == y) continue;
			if (!_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && _roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // 좌
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (_roomInfo[x][y].isWall[0] && !_roomInfo[x][y].isWall[1] && _roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) //  상
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && !_roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) //  우
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && _roomInfo[x][y].isWall[2] && !_roomInfo[x][y].isWall[3]) //  하
			{
				candidate.push_back(Vector2(x, y));
			}
		}
	}

	int move[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} }; // L T R B
	for (int i = 0; i < candidate.size(); i++)
	{
		_roomInfo[candidate[i].x][candidate[i].y].roomType = -1;
		for (int dir = 0; dir < 4; dir++)
		{
			if (!_roomInfo[candidate[i].x][candidate[i].y].isWall[dir])
			{
				int newX = candidate[i].x + move[dir][0];
				int newY = candidate[i].y + move[dir][1];
				_roomInfo[newX][newY].isWall[(dir + 2) % 4] = true; // 없애는 방으로 향하는 길 막아주기
			}
		}
	}

	return true;
}

void StageManager::releaseStage()
{
	for (int i = 0; i < _stageMap.size(); i++)
	{
		for (int j = 0; j < _stageMap[i].size(); j++)
		{
			if (_stageMap[i][j] != nullptr)
			{
				_stageMap[i][j]->release();
				delete _stageMap[i][j];
			}
		}
		_stageMap[i].clear();
	}
	_stageMap.clear();
}

Vector2 StageManager::getPlayerPos()
{
	return _player->getPosition();
}

void StageManager::setPlayerPos( int x, int y)
{
	
	_player->setPosition(Vector2(x, y));
}

void StageManager::showDamage(DamageInfo info, Vector2 pos)
{
	_uiMgr->showDamage(info, pos);
}

void StageManager::showEnemyHp(float maxHp, float curHp, Vector2 pos)
{
	_uiMgr->showEnemyHp(maxHp, curHp, pos);
}


