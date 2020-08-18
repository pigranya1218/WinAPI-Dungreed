#pragma once
#include "GameObject.h"

class NpcManager;

enum class NPC_TYPE : int
{
	RESTAURANT, // �Ĵ�
	SHOP, // ����
};

class Npc : public GameObject
{
protected:
	NpcManager* _npcMgr;

	bool _isActive; // Ȱ��ȭ���ΰ�? (��ȣ�ۿ������� �Ǵ�)
	bool _isClose; // �÷��̾ ������ �ִ°�
	DIRECTION _direction; // �ٶ󺸴� ����

public:
	void setNpcManager(NpcManager* npcMgr) { _npcMgr = npcMgr; }

	virtual void init(Vector2 pos, DIRECTION direction) {};
	bool isActive() { return _isActive; }
};

