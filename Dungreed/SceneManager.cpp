#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

GameNode* SceneManager::_currentScene = NULL;

HRESULT SceneManager::init()
{
	_currentScene = NULL;

	return S_OK;
}

void SceneManager::release()
{
	auto miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void SceneManager::update()
{
	if (_currentScene) _currentScene->update();
}

void SceneManager::render()
{
	if (_currentScene) _currentScene->render();
}

GameNode * SceneManager::addScene(string sceneName, GameNode * scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT SceneManager::changeScene(string sceneName)
{
	auto find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return S_OK;

	if (SUCCEEDED(find->second->init()))
	{
		//� ���� ������ ����ֱ� ������ ������ ���� ���ְ�
		if (_currentScene) _currentScene->release();

		//���� ���� �ٲٷ��� ���� ��´�
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}
