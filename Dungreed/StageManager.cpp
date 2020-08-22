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
	Stage* resultRoom = nullptr;
	switch (stageType)
	{
	case 0: // �Ϲ� ��
	{
		if (!isWall[0] && !isWall[1] && !isWall[2] && !isWall[3]) // ��,��,��,�ϰ� �ո� ���
		{
			int rand = RANDOM->getInt(2);
			if(rand==0) resultRoom = new Room20LTRB;
			else if(rand==1) resultRoom = new Room22LTRB;
		}
		else if (!isWall[0] && !isWall[1] && !isWall[2] && isWall[3])//��,��,��  �ո� ���
		{
			int rand = RANDOM->getInt(2);
			resultRoom = new Room4LTR;
			
		}
		else if (!isWall[0] && isWall[1] && !isWall[2] && !isWall[3])//��, ��, ��  �ո� ���
		{
			int rand = RANDOM->getInt(5);
			if (rand == 0)resultRoom = new Room12LRB;
			else if (rand == 1)resultRoom = new Room20LRB;
			else resultRoom = new Room12LRB;
		}
		else if (!isWall[0] && !isWall[1] && isWall[2] && !isWall[3])//��, ��, ��  �ո� ���
		{
			resultRoom = new Room13LTB;    
		}
		else if (isWall[0] && !isWall[1] && !isWall[2] && !isWall[3])// ��, ��, ��  �ո� ���
		{
			resultRoom = new Room14TRB;
		}
		else if (!isWall[0] && isWall[1] && !isWall[2] && isWall[3])//��, �� �ո� ���
		{
			int rand = RANDOM->getInt(5);
			if(rand==0)resultRoom = new Room21LR;
			else if(rand==1)resultRoom = new Room4LR;
			else if(rand==2)resultRoom = new Room5LR;
			else if (rand == 3)resultRoom = new Room3LR;
			else if (rand == 4)resultRoom = new Room2LR;
			else resultRoom = new Room21LR;
		}
		else if (isWall[0] && !isWall[1] && isWall[2] && !isWall[3])//��, �� �ո� ���
		{
			int rand = RANDOM->getInt(2);
		    if(rand==0) resultRoom = new Room15TB;
			else if(rand==1) resultRoom = new Room4TB;
			else resultRoom = new Room20TB;
		}
		else if (!isWall[0] && !isWall[1] && isWall[2] && isWall[3])//��, �� �ո� ���
		{
			resultRoom = new Room11LT;
		}
		else if (!isWall[0] && isWall[1] && isWall[2] && !isWall[3])//��, �� �ո� ���
		{
			int rand = RANDOM->getInt(5);
			if (rand == 0)resultRoom = new Room12LB;
			else if (rand == 1)resultRoom = new Room20LB;
			else resultRoom = new Room12LB;
		}
		else if (isWall[0] && !isWall[1] && !isWall[2] && isWall[3])//��, �� �ո� ���
		{
			resultRoom = new Room7RT;
		}
		else if (isWall[0] && isWall[1] && !isWall[2] && !isWall[3])//��, �� �ո� ���
		{
			int rand = RANDOM->getInt(2);
			if(rand==0)resultRoom = new Room7_RB;
			else if(rand==1)resultRoom = new Room11_RB;
			else resultRoom = new Room7_RB;
		}
		else if (!isWall[0] && isWall[1] && isWall[2] && isWall[3])//�� �ո� ���
		{
			resultRoom = new Room8L;
		}
		else if (isWall[0] && isWall[1] && !isWall[2] && isWall[3])//�� �ո� ���
		{
			resultRoom = new Room1R;
		}
		else if (isWall[0] && !isWall[1] && isWall[2] && isWall[3])//�� �ո� ���
		{
			resultRoom = new Room10T;
		}
		else if (isWall[0] && isWall[1] && isWall[2] && !isWall[3])//�� �ո� ���
		{
			resultRoom = new Room9B;
		}
	} 
	break;
	case 1: // ���۹�
	{
		if (isWall[0] && isWall[1] && !isWall[2] && isWall[3]) // �� �ո� ���
		{
			resultRoom = new StartRoom1;
		}
		else if (isWall[0] && isWall[1] && !isWall[2] && !isWall[3]) //��, �� �ݸ� ���
		{
			resultRoom = new StartRoom2;

		}
		else if (isWall[0] && isWall[1] && isWall[2] && !isWall[3]) // �� �ݸ� ���
		{
			resultRoom = new StartRoom3;

		}
	}
	break;
	case 2: // ����
	{
		if (!isWall[0] && isWall[1] && isWall[2] && isWall[3]) // �� �ո� ���
		{
			resultRoom = new DownStair1L;
		}
		else if (!isWall[0] && !isWall[1] && isWall[2] && isWall[3]) //��, ��
		{
			resultRoom = new DownStair2LT;

		}
		else if (isWall[0] && !isWall[1] && isWall[2] && isWall[3]) //��
		{
			resultRoom = new DownStair2T;

		}
	}
	break;
	case 3: // �Ĵ��
	{
		if (!isWall[0] && isWall[1] && isWall[2] && isWall[3]) // �°� �ո� ���
		{
			resultRoom = new RestaurantRoom;
		}
		else if (!isWall[0] && isWall[1] && !isWall[2] && isWall[3]) // ��, �찡 �ո� ���
		{
			resultRoom = new RestaurantRoom2LR;
		}
		else if (isWall[0] && isWall[1] && !isWall[2] && isWall[3]) // �찡 �ո� ���
		{
			resultRoom = new RestaurantRoom1R;
		}
	}
	break;
	case 4: // ������
	{
		if (!isWall[0] && isWall[1] && !isWall[2] && isWall[3]) // ��, �찡 �ո� ���
		{
			resultRoom = new DungeonShopRoom3;
		}
		else if (!isWall[0] && isWall[1] && isWall[2] && isWall[3]) // �°� �ո� ���
		{
			resultRoom = new DungeonShopRoom;
		}
		else if (isWall[0] && isWall[1] && !isWall[2] && isWall[3]) // �찡 �ո� ���
		{
			resultRoom = new DungeonShopRoom2;
		}
	}
	break;
	}

	resultRoom->setPlayer(_player);
	resultRoom->setStageManager(this);
	resultRoom->setUIManager(_uiMgr);
	vector<bool> wallInfo{ isWall[0], isWall[1], isWall[2], isWall[3] };
	resultRoom->setWall(wallInfo);
	resultRoom->init();
	return resultRoom;
}

string StageManager::getStageTitle()
{
	switch (_currStageType)
	{
	case STAGE_TYPE::TEST:
		return "�׽�Ʈ �����";
	case STAGE_TYPE::VILLAGE:
		return "����";
	case STAGE_TYPE::DUNGEON_NORMAL:
		return "1�� : ���� ����";
	case STAGE_TYPE::DUNGEON_BOSS:
		return "2�� : �������� ����";
	}
}

void StageManager::init()
{
	_currStageType = STAGE_TYPE::VILLAGE;
	_mapSize = 4;
	makeStage();
	_uiMgr->setMap(_stageMap, getStageTitle());
	_uiMgr->setCurrentMapIndex(Vector2(_currIndexX, _currIndexY));
}

void StageManager::release()
{
	
	releaseStage();
}

void StageManager::update(float const elapsedTime)
{
	/*if (KEY_MANAGER->isOnceKeyDown('A'))
	{
		moveRoom(Vector2(-1, 0));
	}
	else if (KEY_MANAGER->isOnceKeyDown('D'))
	{
		moveRoom(Vector2(1, 0));
	}
	else if (KEY_MANAGER->isOnceKeyDown('W'))
	{
		moveRoom(Vector2(0, -1));
	}
	else if (KEY_MANAGER->isOnceKeyDown('S'))
	{
		moveRoom(Vector2(0, 1));
	}*/
	_currStage->update(elapsedTime);
}

void StageManager::render()
{
	_currStage->render();
	
}

bool StageManager::attack(FloatRect* rect, AttackInfo* info)
{
	if (info->team == OBJECT_TEAM::PLAYER)
	{
		return _currStage->isHitEnemy(rect, info);
	}
	else
	{
		if (_player->isHit(rect, info))
		{
			return _player->hitEffect(rect, info);
		}
	}
	return false;
}

bool StageManager::attack(FloatCircle* circle, AttackInfo* info)
{
	if (info->team == OBJECT_TEAM::PLAYER)
	{
		return _currStage->isHitEnemy(circle, info);
	}
	else
	{
		if (_player->isHit(circle, info))
		{
			return _player->hitEffect(circle, info);
		}
	}
	return false;
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
	int moveType = 0;
	if (moveDir.x == -1)
	{
		moveType = 2;
	}
	else if (moveDir.x == 1)
	{
		moveType = 0;
	}
	else if (moveDir.y == -1)
	{
		moveType = 3;
	}
	else if (moveDir.y == 1)
	{
		moveType = 1;
	}
	_uiMgr->setCurrentMapIndex(Vector2(_currIndexX, _currIndexY));
	_currStage->enter(moveType);
	_gameScene->pushR2REvent(1);
}

void StageManager::moveRoomIndex(Vector2 index)
{
	_currIndexX = index.x;
	_currIndexY = index.y;
	_currStage = _stageMap[_currIndexX][_currIndexY];

	_uiMgr->setCurrentMapIndex(Vector2(_currIndexX, _currIndexY));
	_currStage->enter(4);
	_gameScene->pushR2REvent(1);
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
		_currStage->setUIManager(_uiMgr);
		_currStage->setPlayer(_player);
		_currStage->init();
		_currStage->enter(0);
		
		break;
	case STAGE_TYPE::DUNGEON_NORMAL:
		makeDungeon();
		_uiMgr->setMap(_stageMap, getStageTitle());
		_uiMgr->setCurrentMapIndex(Vector2(_currIndexX, _currIndexY));
		break;
	case STAGE_TYPE::DUNGEON_BOSS:
		
		_currStage = new BossRoomBef1R;
		_currStage->setStageManager(this);
		_currStage->setUIManager(_uiMgr);
		_currStage->setPlayer(_player);
		_currStage->init();
		_currStage->enter(0);
		
		break;
	case STAGE_TYPE::TEST:
		_currStage = new DebugStage();
		_currStage->setStageManager(this);
		_currStage->setUIManager(_uiMgr);
		_currStage->setPlayer(_player);
		_currStage->init();
		_currStage->enter(0);
		break;
	default:
		break;
	}
}

void StageManager::makeBossStage()
{
	for (int i = 0; i < 3; i++)
	{
		if(i==0)_currStage = new BossRoomBef1R;
		else if(i==1)_currStage = new BossRoom1;
		else if(i==2)_currStage = new DownStair1L;
		_currStage->setStageManager(this);
		_currStage->setUIManager(_uiMgr);
		_currStage->setPlayer(_player);
		_currStage->init();
		
		_bossRoomInfo.push_back(_currStage);
	}
	_currStage = _bossRoomInfo[0];
	_currStage->setStageManager(this);
	_currStage->setUIManager(_uiMgr);
	_currStage->setPlayer(_player);
	_currStage->init();
	_currStage->enter(0);
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
		// �� ���� �ʱ�ȭ
		for (int x = 0; x < _mapSize; x++)
		{
			for (int y = 0; y < _mapSize; y++)
			{
				for (int dir = 0; dir < 4; dir++)
				{
					_roomInfo[x][y].isWall[dir] = true;
				}
				_roomInfo[x][y].isVisited = false;
				_roomInfo[x][y].roomType = 0;
			}
		}
		int startX = RANDOM->getInt(_mapSize);
		int startY = RANDOM->getInt(_mapSize);
		makeRoom(startX, startY);

		if (makeSpecialRoom()) // ���۹�, ����, �Ĵ��, �������� ���� �� �ִ� ���̶�� ����
		{
			break;
		}
	}

	// ������ ������ �´� �� �����
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
	_currStage->enter(0);
}

void StageManager::makeRoom(int x, int y)
{
	if (_roomInfo[x][y].isVisited) return;
	_roomInfo[x][y].isVisited = true;

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
	// ������ �����
	vector<Vector2> candidate;
	Vector2 start;
	Vector2 end;
	Vector2 restaurant;
	Vector2 shop;

	for (int x = 0; x < _mapSize; x++)
	{
		for (int y = 0; y < _mapSize; y++)
		{
			if (_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && !_roomInfo[x][y].isWall[2] && !_roomInfo[x][y].isWall[3]) // �� ��
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && !_roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // ��
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && _roomInfo[x][y].isWall[2] && !_roomInfo[x][y].isWall[3]) // ��
			{
				candidate.push_back(Vector2(x, y));
			}
		}
	}

	if (candidate.size() == 0) return false;
	int random = RANDOM->getInt(candidate.size());
	start = candidate[random];
	_roomInfo[start.x][start.y].roomType = 1;

	// ���� �����
	candidate.clear();
	for (int x = 0; x < _mapSize; x++)
	{
		for (int y = 0; y < _mapSize; y++)
		{
			if (start.x == x && start.y == y) continue;
			if (!_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && _roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // ��
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (_roomInfo[x][y].isWall[0] && !_roomInfo[x][y].isWall[1] && _roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // ��
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (!_roomInfo[x][y].isWall[0] && !_roomInfo[x][y].isWall[1] && _roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // ��, ��
			{
				candidate.push_back(Vector2(x, y));
			}
		}
	}

	if (candidate.size() == 0) return false;
	random = RANDOM->getInt(candidate.size());
	end = candidate[random];
	_roomInfo[end.x][end.y].roomType = 2;

	// �Ĵ� �����
	candidate.clear();
	for (int x = 0; x < _mapSize; x++)
	{
		for (int y = 0; y < _mapSize; y++)
		{
			if (start.x == x && start.y == y) continue;
			if (end.x == x && end.y == y) continue;
			if (!_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && !_roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // �� ��
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (!_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && _roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // ��
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && !_roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // ��
			{
				candidate.push_back(Vector2(x, y));
			}
		}
	}

	if (candidate.size() == 0) return false;
	random = RANDOM->getInt(candidate.size());
	restaurant = candidate[random];
	_roomInfo[restaurant.x][restaurant.y].roomType = 3;

	// ���� �����
	candidate.clear();
	for (int x = 0; x < _mapSize; x++)
	{
		for (int y = 0; y < _mapSize; y++)
		{
			if (start.x == x && start.y == y) continue;
			if (end.x == x && end.y == y) continue;
			if (restaurant.x == x && restaurant.y == y) continue;
			if (!_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && !_roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // �� ��
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (!_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && _roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // ��
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && !_roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // ��
			{
				candidate.push_back(Vector2(x, y));
			}
		}
	}

	if (candidate.size() == 0) return false;
	random = RANDOM->getInt(candidate.size());
	shop = candidate[random];
	_roomInfo[shop.x][shop.y].roomType = 4;

	// �������� ����� �� �� �����
	candidate.clear();
	for (int x = 0; x < _mapSize; x++)
	{
		for (int y = 0; y < _mapSize; y++)
		{
			if (start.x == x && start.y == y) continue;
			if (end.x == x && end.y == y) continue;
			if (restaurant.x == x && restaurant.y == y) continue;
			if (shop.x == x && shop.y == y) continue;
			if (!_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && _roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) // ��
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (_roomInfo[x][y].isWall[0] && !_roomInfo[x][y].isWall[1] && _roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) //  ��
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && !_roomInfo[x][y].isWall[2] && _roomInfo[x][y].isWall[3]) //  ��
			{
				candidate.push_back(Vector2(x, y));
			}
			else if (_roomInfo[x][y].isWall[0] && _roomInfo[x][y].isWall[1] && _roomInfo[x][y].isWall[2] && !_roomInfo[x][y].isWall[3]) //  ��
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
				_roomInfo[newX][newY].isWall[(dir + 2) % 4] = true; // ���ִ� ������ ���ϴ� �� �����ֱ�
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

Vector2 StageManager::getEnemyPos(Vector2 pos)
{
	return _currStage->getEnemyPos(pos);
}

void StageManager::showDamage(DamageInfo info, Vector2 pos)
{
	_uiMgr->showDamage(info, pos);
}

void StageManager::showEnemyHp(float maxHp, float curHp, Vector2 pos)
{
	_uiMgr->showEnemyHp(maxHp, curHp, pos);
}


