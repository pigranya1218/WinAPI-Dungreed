#include "stdafx.h"
#include "Stage.h"
#include "NpcManager.h"
#include "RestaurantNpc.h"
#include "ShopNpc.h"
#include "AbilityNpc.h"
#include "CostumeNpc.h"
#include "GateNpc.h"
#include "ChestNpc.h"
#include "DoorNpc.h"
#include "UIManager.h"

void NpcManager::init()
{
}

void NpcManager::release()
{
	for (int i = 0; i < _npcs.size(); i++)
	{
		_npcs[i]->release();
	}
}

void NpcManager::update(float elapsedTime)
{
	for (int i = 0; i < _npcs.size();)
	{
		_npcs[i]->update(elapsedTime);
		if (!_npcs[i]->getActive())
		{
			_npcs[i]->release();
			delete _npcs[i];
			_npcs.erase(_npcs.begin() + i);
		}
		else 
		{
			i++;
		}
	}
}

void NpcManager::render()
{
	for (int i = 0; i < _npcs.size(); i++)
	{
		_npcs[i]->render();
	}
}

void NpcManager::spawnNpc(NPC_TYPE type, Vector2 pos, DIRECTION direction)
{
	Npc* npc = nullptr;
	switch (type)
	{
	case NPC_TYPE::RESTAURANT:
	{
		npc = new RestaurantNpc;
	}
	break;
	case NPC_TYPE::SHOP:
	{
		npc = new ShopNpc;
	}
	break;
	case NPC_TYPE::GATE:
	{
		npc = new GateNpc;
	}
	break;
	case NPC_TYPE::ABILITY:
	{
		npc = new AbilityNpc;
	}
	break;
	case NPC_TYPE::COSTUME:
	{
		npc = new CostumeNpc;
	}
	break;
	case NPC_TYPE::CHEST_BASIC:
	{
		ChestNpc * chestNpc = new ChestNpc;
		chestNpc->setRank(0);
		chestNpc->setObjectManager(_objectMgr);
		npc = chestNpc;
	}
	break;
	case NPC_TYPE::CHEST_BLUE:
	{
		ChestNpc* chestNpc = new ChestNpc;
		chestNpc->setRank(1);
		chestNpc->setObjectManager(_objectMgr);
		npc = chestNpc;
	}
	break;
	case NPC_TYPE::CHEST_YELLOW:
	{
		ChestNpc* chestNpc = new ChestNpc;
		chestNpc->setRank(2);
		chestNpc->setObjectManager(_objectMgr);
		npc = chestNpc;
	}
	break;
	case NPC_TYPE::CHEST_BOSS:
	{
		ChestNpc* chestNpc = new ChestNpc;
		chestNpc->setRank(3);
		chestNpc->setObjectManager(_objectMgr);
		npc = chestNpc;
	}
	break;
	case NPC_TYPE::ENTRANCE:
	case NPC_TYPE::EXIT:
	{
		DoorNpc* doorNpc = new DoorNpc;
		doorNpc->setType(type);
		npc = doorNpc;
	}
	break;
	}
	npc->init(pos, direction);
	npc->setNpcManager(this);
	npc->setUIManager(_uiMgr);
	_npcs.push_back(npc);
}

Vector2 NpcManager::getPlayerPos()
{
	return _stage->getPlayerPos();
}

void NpcManager::moveTo(GameObject* gameObject, Vector2 moveDir)
{
	_stage->moveTo(gameObject, moveDir);
}

vector<tagShowNpc> NpcManager::getNpcInfos()
{
	vector<tagShowNpc> result;
	for (int i = 0; i < _npcs.size(); i++)
	{
		if (_npcs[i]->getMapIcon() != nullptr)
		{
			tagShowNpc info;
			info.icon = _npcs[i]->getMapIcon();
			info.type = _npcs[i]->getType();
			result.push_back(info);
		}
	}
	return result;
}

void NpcManager::moveRoom(Vector2 pos)
{
	_stage->moveToIndex(pos);
}

void NpcManager::nextStage()
{
	_stage->nextStage();
}

Vector2 NpcManager::getGatePos()
{
	for(int i = 0 ; i < _npcs.size(); i++)
	{
		if (_npcs[i]->getType() == NPC_TYPE::GATE)
		{
			return _npcs[i]->getPosition();
		}
	}
	return Vector2(0, 0);
}

void NpcManager::setShowPlayer(bool showPlayer)
{
	_stage->setShowPlayer(showPlayer);
}

void NpcManager::showRestaurantUI()
{
	_uiMgr->showRestaurant();
}

void NpcManager::showShopUI()
{
	_uiMgr->showShop();
}

void NpcManager::showAbilityUI()
{
	_uiMgr->showAbility();
}

void NpcManager::showCostumeUI()
{
	_uiMgr->showCostume();
}
