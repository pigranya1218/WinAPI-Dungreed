#pragma once
#include "SingletonBase.h"
#include "AllEnums.h"


class DebugManager : public SingletonBase<DebugManager>
{
private:
	bitset<(int)(DEBUG_TYPE::END)> _isDebug;

public:
	void init();
	void update();
	bool isDebugMode(DEBUG_TYPE type);
};

