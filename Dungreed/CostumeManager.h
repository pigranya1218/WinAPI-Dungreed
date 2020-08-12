#pragma once
#include<map>

class Costume;
enum class COSTUME_TYPE;

class CostumeManager
{
private:
	map<COSTUME_TYPE, Costume*> _costumeMap;

public:
	void init();
	void release();

	Costume* getCostume(COSTUME_TYPE type) const { return _costumeMap.find(type)->second; }
};

