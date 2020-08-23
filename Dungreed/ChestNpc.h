#pragma once
#include "Npc.h"

class ObjectManager;

class ChestNpc : public Npc
{
private:
	Image* _img;
	string _imgName;
	int _rank; // 0 : 기본  -> 2 : 좋은 상자 , 3 : 보스 상자

	ObjectManager* _objectMgr;

private:
	void setInfo(); // 랭크에 따른 인포 저장
	Item* getItem();

public:
	void setRank(int rank) { _rank = rank; };
	void setObjectManager(ObjectManager* objectManager) { _objectMgr = objectManager; }

	virtual void init(Vector2 pos, DIRECTION direction);
	virtual void interaction();
	virtual void render();
};

