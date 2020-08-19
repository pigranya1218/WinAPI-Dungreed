#include "stdafx.h"
#include "StageManager.h"
#include "GameScene.h"
#include "Player.h"
#include "UIManager.h"

#include "DebugStage.h"
#include "VillageStage.h"

#include "AllRoom.h"


void StageManager::init()
{
	_currStageType = STAGE_TYPE::TEST;
	//_currStageType = STAGE_TYPE::VILLAGE;
	
	makeStage();

	_roomIndex = 0;


	rnd = RANDOM->getFromIntTo(0, 5);
	k = RANDOM->getFromIntTo(0, 10);
	l = RANDOM->getFromIntTo(0, 10);
	_currIndexX = k;
	_currIndexY = l;
	
}

void StageManager::release()
{
	releaseStage();
}

void StageManager::update(float const elapsedTime)
{
	if (_currStageType == STAGE_TYPE::DUNGEON_NORMAL)
	{
		/*if (_roomIndex >= _stages.size())return;
			
		_stages[_roomIndex]->update(elapsedTime);*/
		_vStage[_currIndexX][_currIndexY]->update(elapsedTime);

	}

	else	_currStage->update(elapsedTime);
}

void StageManager::render()
{
	if (_currStageType == STAGE_TYPE::DUNGEON_NORMAL)
	{
		/*if (_roomIndex >= _stages.size())return;
		_stages[_roomIndex]->render();*/
		_vStage[_currIndexX][_currIndexY]->render();
	}
	else _currStage->render();
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
	if (_currStageType == STAGE_TYPE::DUNGEON_NORMAL)
	{
		/*if (_roomIndex >= _stages.size())return;
		_stages[_roomIndex]->moveTo(object, moveDir);*/
		_vStage[_currIndexX][_currIndexY]->moveTo(object, moveDir);
	}
	else _currStage->moveTo(object, moveDir);


	
}

void StageManager::nextStage()
{
	_currStageType = static_cast<STAGE_TYPE>(static_cast<int>(_currStageType) + 1);
	releaseStage();
	makeStage();
}

void StageManager::moveRoom()
{
	_currIndexX += 1;
	//_currIndexY += 1;
	//_roomIndex += 1;
}

void StageManager::makeStage()
{
	_vStage.resize(10);
	for (int i = 0; i < 10; i++)
	{
		_vStage[i].resize(10);
	}
	
	switch (_currStageType)
	{
	case STAGE_TYPE::VILLAGE:
		_currStage = new VillageStage();
		_currStage->setStageManager(this);
		_currStage->init();
		break;
	case STAGE_TYPE::DUNGEON_NORMAL:
		
	
		_currStage = new StartRoom1();
	
		//_stages.push_back(_currStage);

		_vStage[k][l] = _currStage;

		_vStage[_currIndexX][_currIndexY]->setStageManager(this);
		_vStage[_currIndexX][_currIndexY]->init();

		if (_currStage->getOpenDirection(0))
		{
			//_stage = new Room4LR();
			if (rnd == 0)_stage = new Room20LTRB();
			else if (rnd == 1)_stage = new Room2LTR();
			else if (rnd == 2)_stage = new Room4LR();
			else if (rnd == 3)_stage = new Room21LR();
			else if (rnd == 4)_stage = new Room22LTRB();
			else _stage = new Room20LTRB();


			_vStage[k - 1][l] = _stage;
		}
		if (_currStage->getOpenDirection(1))
		{
			if (rnd == 0)_stage = new Room20LTRB;
			else if (rnd == 1)_stage = new Room22LTRB;
			else if (rnd == 2)_stage = new Room2LTR;
			else _stage = new Room20LTRB;


			_vStage[k][l - 1] = _stage;
		}
		if (_currStage->getOpenDirection(2))
		{
			//_stage = new Room4LR();
			if (rnd == 0)_stage = new Room20LTRB();
			else if (rnd == 1)_stage = new Room2LTR();
			else if (rnd == 2)_stage = new Room4LR();
			else if (rnd == 3)_stage = new Room21LR();
			else if (rnd == 4)_stage = new Room22LTRB();
			else _stage = new Room20LTRB();

			
			_vStage[k + 1][l] = _stage;
		}

		if (_currStage->getOpenDirection(3))
		{
			if (rnd == 0)_stage = new Room20LTRB;
			else if (rnd == 1)_stage = new Room22LTRB;
			else if (rnd == 2)_stage = new Room2LTR;
			else _stage = new Room20LTRB;


			_vStage[k][l+1] = _stage;
		}
		

		/*_vStage[_currIndexX][_currIndexY]->setStageManager(this);
		_vStage[_currIndexX][_currIndexY]->init();*/
		
		/*for (iter = _currStage->getStageDirection().begin(); iter != _currStage->getStageDirection().end();)
				{
					switch (*iter)
					{
					case DIRECTION::RIGHT:

						if (rnd == 0)_currStage = new Room20LTRB();
						else if (rnd == 1)_currStage = new Room2LTR();
						else if (rnd == 2)_currStage = new Room4LR();
						else if (rnd == 3)_currStage = new Room21LR();
						else if (rnd == 4)_currStage = new Room22LTRB();
						else _currStage = new Room20LTRB();

						_vStage[k][l + 1] = _currStage;

						break;
					case DIRECTION::LEFT:
						break;
					case DIRECTION::UP:
						break;
					case DIRECTION::DOWN:
						if (rnd == 0)_currStage = new Room20LTRB;
						else if (rnd == 1)_currStage = new Room22LTRB;
						else if (rnd == 2)_currStage = new Room2LTR;
						else _currStage = new Room20LTRB;


						_vStage[k + 1][l] = _currStage;

						break;
					default:
						break;
					}
					++iter;
				}*/

		/*_restaurantRoom = new RestaurantRoom();
		
	    _downStair = new StartRoom1();
		
		 _shopRoom = new DungeonShopRoom();*/
		

	


		//일단 방을 _stages에 넣고
		//_stages.push_back(_currStage);
		//그걸 벡터에 넣어서 이중 구조로
	    //_vStage.push_back(_stages);

		//이런 느낌으로 접근 가능
	/*	for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{

				int k = RANDOM->getFromIntTo(0, 10);
				int l = RANDOM->getFromIntTo(0, 10);

				_vStage[k][l] = _currStage;
			}
		}
		*/

		
		/*for (iter = _currStage->getStageDirection().begin(); iter != _currStage->getStageDirection().end(); ++iter)
		{
			switch (*iter)
			{
			case DIRECTION::RIGHT:
			

				break;
			case DIRECTION::LEFT:
				break;
			case DIRECTION::UP:
				break;
			case DIRECTION::DOWN:
				break;
			default:
				break;
			}
			
			
		}*/
		//for (int i = 0; i < 10; i++)
		//{
		//	for (int j = 0; j < 10; j++)
		//	{
		//		if (i == 0 && j == 0)
		//		{
		//			int rnd = RANDOM->getInt(2);
		//			if (rnd == 0) _currStage = new StartRoom1();
		//			 else _currStage= new StartRoom2() ;
		//			//일단 방을 _stages에 넣고
		//			_stages.push_back(_currStage);
		//			//그걸 벡터에 넣어서 이중 구조로
		//			_vStage.push_back(_stages);
		//		}

		//	}
		//}


		/*_currStage = new StartRoom1();
		_stages.push_back(_currStage);

		_currStage = new Room1();
		_stages.push_back(_currStage);

		_currStage = new Room2();
		_stages.push_back(_currStage);

		_currStage = new RestaurantRoom();
		_stages.push_back(_currStage);

		_currStage = new DungeonShopRoom();
		_stages.push_back(_currStage);
		
		_stages[_roomIndex]->setStageManager(this);
		_stages[_roomIndex]->init();*/

		break;
	case STAGE_TYPE::DUNGEON_BOSS:
		break;
	case STAGE_TYPE::TEST:
		_currStage = new DebugStage();
		_currStage->setStageManager(this);
		_currStage->setUIManager(_uiMgr);
		_currStage->setPlayer(_player);
		_currStage->init();
		break;
	default:
		break;
	}

	
	
	//_currStage = new RestaurantRoom();
	
	

}

void StageManager::releaseStage()
{
	for (int i = 0; i < _stages.size(); i++)
	{
		_stages[i]->release();
		delete _stages[i];
	}
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


