#include "stdafx.h"
#include "Stage.h"
#include "NpcManager.h"
#include "RestaurantNpc.h"
#include "GateNpc.h"

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

	}
	break;
	case NPC_TYPE::GATE:
	{
		npc = new GateNpc;
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
