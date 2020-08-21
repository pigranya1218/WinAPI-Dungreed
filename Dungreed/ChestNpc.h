#pragma once
#include "Npc.h"

class ChestNpc : public Npc
{
private:
	Image* _img;
	string _imgName;
	int _rank; // 0 : �⺻  -> 2 : ���� ���� , 3 : ���� ����

private:
	void setInfo(); // ��ũ�� ���� ���� ����
		
public:
	void setRank(int rank) { _rank = rank; };

	virtual void init(Vector2 pos, DIRECTION direction);
	virtual void interaction();
	virtual void render();
};

