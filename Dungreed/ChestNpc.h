#pragma once
#include "Npc.h"

class ObjectManager;

class ChestNpc : public Npc
{
private:
	Image* _img;
	string _imgName;
	int _rank; // 0 : �⺻  -> 2 : ���� ���� , 3 : ���� ����

	ObjectManager* _objectMgr;

private:
	void setInfo(); // ��ũ�� ���� ���� ����
	Item* getItem();

public:
	void setRank(int rank) { _rank = rank; };
	void setObjectManager(ObjectManager* objectManager) { _objectMgr = objectManager; }

	virtual void init(Vector2 pos, DIRECTION direction);
	virtual void interaction();
	virtual void render();
};

