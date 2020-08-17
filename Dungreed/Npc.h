#pragma once
#include "GameObject.h"

class NpcManager;

enum class NPC_TYPE : int
{
	RESTAURANT, // 식당
	SHOP, // 상점
};

class Npc : public GameObject
{
protected:
	NpcManager* _npcMgr;

	bool _isActive; // 활성화중인가? (상호작용중인지 판단)
	bool _isClose; // 플레이어가 가까이 있는가
	DIRECTION _direction; // 바라보는 방향

public:
	void setNpcManager(NpcManager* npcMgr) { _npcMgr = npcMgr; }

	virtual void init(Vector2 pos, DIRECTION direction) {};
	bool isActive() { return _isActive; }
};

