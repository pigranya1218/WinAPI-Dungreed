#include "stdafx.h"
#include "keyManager.h"

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

HRESULT KeyManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyUp().set(i, false);
	}

	return S_OK;
}

void KeyManager::release()
{
}

bool KeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) // �����ִٸ�
	{
		if (!this->getKeyDown()[key]) // ������ �������� �ʾҴٸ�
		{
			_bufferDown.push_back(key);
			// this->setKeyDown(key, true);

			return true;
		}
	}
	else // �������� �ʴٸ�
	{
		this->setKeyDown(key, false);
	}

	return false;
}

bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) // �����ִٸ�
	{
		this->setKeyUp(key, true);
	}
	else // �������� �ʴٸ�
	{
		if (this->getKeyUp()[key]) // ������ �������ٸ�
		{
			_bufferUp.push_back(key); 
			// this->setKeyUp(key, false);

			return true;
		}
	}

	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;

	return false;
}

bool KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;

	return false;
}

void KeyManager::update()
{
	for (int i = 0; i < _bufferDown.size(); i++)
	{
		this->setKeyDown(_bufferDown[i], true);
	}
	for (int i = 0; i < _bufferUp.size(); i++)
	{
		this->setKeyUp(_bufferUp[i], false);
	}
	_bufferDown.clear();
	_bufferUp.clear();
}

int KeyManager::getWhichKeyDown()
{
	int result = -1;
	for (int i = 0x20; i < KEYMAX; i++)
	{
		if (isOnceKeyDown(i))
		{
			result = i;
			break;
		}
	}
	return result;
}
