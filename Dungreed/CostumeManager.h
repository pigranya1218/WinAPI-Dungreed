#pragma once
#include<map>
#include "Costume.h"

class CostumeManager
{
private:
	map<COSTUME_TYPE, Costume*> _costumeMap;
	//Costume* _costume;
public:
	void init();
	void release();
	void update();
	void render();

	Costume* getCostume(COSTUME_TYPE type) const { return _costumeMap.find(type)->second; };
};

