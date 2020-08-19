#include "stdafx.h"
#include "Stage.h"
#include "NpcManager.h"
#include "RestaurantNpc.h"

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
	for (int i = 0; i < _npcs.size(); i++)
	{
		_npcs[i]->update(elapsedTime);
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
	switch (type)
	{
	case NPC_TYPE::RESTAURANT:
	{
		RestaurantNpc* npc = new RestaurantNpc;
		npc->init(pos, direction);
		npc->setNpcManager(this);
		npc->setUIManager(_uiMgr);
		_npcs.push_back(npc);
	}
	break;
	case NPC_TYPE::SHOP:
	{

	}
	break;
	}
}

Vector2 NpcManager::getPlayerPos()
{
	return _stage->getPlayerPos();
}
