#pragma once
#include "Npc.h"

class ChestNpc : public Npc
{
private:
	Image* _img;
	string _imgName;
	int _rank; // 0 : 기본  -> 2 : 좋은 상자 , 3 : 보스 상자

private:
	void setInfo(); // 랭크에 따른 인포 저장
		
public:
	void setRank(int rank) { _rank = rank; };

	virtual void init(Vector2 pos, DIRECTION direction);
	virtual void interaction();
	virtual void render();
};

