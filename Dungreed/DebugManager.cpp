#include "stdafx.h"
#include "DebugManager.h"

void DebugManager::init()
{
	for (int i = 0; i < _isDebug.size(); i++)
	{
		_isDebug.set(i, false);
	}
}

void DebugManager::update()
{
	/*if (KEY_MANAGER->isOnceKeyDown(VK_F1))
	{
		_isDebug.flip((int)DEBUG_TYPE::PLAYER);
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_F2))
	{
		_isDebug.flip((int)DEBUG_TYPE::ENEMY);
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_F3))
	{
		_isDebug.flip((int)DEBUG_TYPE::OBJECT);
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_F4))
	{
		_isDebug.flip((int)DEBUG_TYPE::STAGE);
	}*/
}

bool DebugManager::isDebugMode(DEBUG_TYPE type)
{
	return _isDebug[(int) type];
}
